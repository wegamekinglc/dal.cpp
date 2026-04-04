//
// Created by wegam on 2023/2/18.
//

#include <dal/math/aad/expr.hpp>
#include <dal/math/aad/tape.hpp>

#ifndef DAL_USE_XAD_AAD
namespace Dal::AAD {

    namespace {
        auto Begin(Tape_& tape) -> Tape_::Iterator_ {
            return tape.nodes_.Begin();
        }

        auto End(Tape_& tape) -> Tape_::Iterator_ {
            return tape.nodes_.End();
        }

        auto MarkIt(Tape_& tape) -> Tape_::Iterator_ {
            return tape.nodes_.Mark();
        }

        void PropagateAdjoints(Tape_::Iterator_ propagateFrom, Tape_::Iterator_ propagateTo) {
            auto it = propagateFrom;
            while (it != propagateTo) {
                it->PropagateOne();
                --it;
            }
            it->PropagateOne();
        }
    }

    void PropagateMarkToStart(Tape_& tape) {
        PropagateAdjoints(std::prev(MarkIt(tape)), Begin(tape));
    }

    void PropagateToStart(Tape_& tape) {
        PropagateAdjoints(std::prev(End(tape)), Begin(tape));
    }

    void PropagateToMark(Tape_& tape) {
        PropagateAdjoints(std::prev(End(tape)), MarkIt(tape));
    }

    void Clear(Tape_& tape) {
        tape.adjointsMulti_.Clear();
        tape.ders_.Clear();
        tape.argPtrs_.Clear();
        tape.nodes_.Clear();
    }

    void Mark(Tape_& tape) {
        if (Tape_::multi_)
            tape.adjointsMulti_.SetMark();
        tape.ders_.SetMark();
        tape.argPtrs_.SetMark();
        tape.nodes_.SetMark();
    }

    void Rewind(Tape_& tape)  {
        if (Tape_::multi_)
            tape.adjointsMulti_.Rewind();
        tape.ders_.Rewind();
        tape.argPtrs_.Rewind();
        tape.nodes_.Rewind();
    }

    void RewindToMark(Tape_& tape) {
        if (Tape_::multi_)
            tape.adjointsMulti_.RewindToMark();
        tape.ders_.RewindToMark();
        tape.argPtrs_.RewindToMark();
        tape.nodes_.RewindToMark();
    }

    void NewRecording(Tape_&) {}
    void Activate(Tape_&) {}
    void Deactivate(Tape_&) {}
} // namespace Dal::AAD
#else
#include <unordered_map>

namespace Dal::AAD {
    namespace {
        struct TapeState_ {
            Tape_::position_type start_{};
            Tape_::position_type mark_{};
        };

        thread_local std::unordered_map<Tape_*, TapeState_> tape_state_;

        auto State(Tape_& tape) -> TapeState_& {
            auto [it, inserted] = tape_state_.try_emplace(&tape);
            if (inserted) {
                it->second.start_ = tape.getPosition();
                it->second.mark_ = it->second.start_;
            }
            return it->second;
        }
    }

    void Clear(Tape_& tape) {
        auto& state = State(tape);
        tape.clearAll();
        state.start_ = tape.getPosition();
        state.mark_ = state.start_;
    }

    void Mark(Tape_& tape) {
        auto& state = State(tape);
        state.mark_ = tape.getPosition();
    }

    void Rewind(Tape_& tape) {
        auto& state = State(tape);
        tape.resetTo(state.start_);
    }

    void RewindToMark(Tape_& tape) {
        auto& state = State(tape);
        tape.resetTo(state.mark_);
    }

    void PropagateMarkToStart(Tape_& tape) {
        auto& state = State(tape);
        RewindToMark(tape);
        tape.computeAdjointsTo(state.start_);
    }

    void PropagateToStart(Tape_& tape) {
        auto& state = State(tape);
        tape.computeAdjointsTo(state.start_);
    }

    void PropagateToMark(Tape_& tape) {
        auto& state = State(tape);
        tape.computeAdjointsTo(state.mark_);
    }

    void NewRecording(Tape_& tape) {
        auto& state = State(tape);
        tape.newRecording();
        state.start_ = tape.getPosition();
        state.mark_ = state.start_;
    }

    void Activate(Tape_& tape) {
        tape.activate();
    }

    void Deactivate(Tape_& tape) {
        tape.deactivate();
    }
} // namespace Dal::AAD
#endif

