#pragma once

#include <RE/Skyrim.h>
#include "ProfilingConfig.h"

namespace Profiling {
#pragma warning(push)
#pragma warning(disable : 4251)

    class __declspec(dllexport) ProfilingHook {
    public:
        [[nodiscard]] static ProfilingHook& GetSingleton() noexcept;

        static void InstallHook();

    private:
        ProfilingHook() = default;
        ProfilingHook(const ProfilingHook&) = delete;
        ProfilingHook(ProfilingHook&&) = delete;
        ~ProfilingHook() = default;

        ProfilingHook& operator=(const ProfilingHook&) = delete;
        ProfilingHook& operator=(ProfilingHook&&) = delete;

        /** Configs which are currently actively running. */
        std::unordered_map<std::string, ProfilingConfig> activeConfigs;
    };

    static RE::BSFixedString* FuncCallHook(
        RE::BSScript::Internal::VirtualMachine* _this,
        RE::BSScript::Stack* a_stack,
        RE::BSTSmartPointer<RE::BSScript::Internal::IFuncCallQuery>& a_funcCallQuery);

    static inline REL::Relocation<decltype(FuncCallHook)> _original_func;
    static std::unique_ptr<spdlog::logger> outputLogger;
    static uint64_t numStacksPrinted = 0;
    static const uint64_t stacksPrintCap = 10'000;

#pragma warning(pop)
}  // namespace Profiling