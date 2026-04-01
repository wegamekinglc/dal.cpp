//
// Created by wegam on 2023/2/18.
//

#include <dal/math/aad/expr.hpp>
#include <dal/math/aad/tape.hpp>

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


} // namespace Dal::AAD