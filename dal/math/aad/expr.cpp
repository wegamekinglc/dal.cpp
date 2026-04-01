//
// Created by wegam on 2024/9/1.
//

#include <dal/math/aad/expr.hpp>


namespace Dal::AAD {
    thread_local std::mutex tape_mutex_{};
    thread_local Tape_* tape_ = nullptr;
}