//
// Created by tv on 09.08.23.
//

#ifndef ENGINE_REFLECTABLECLASS_H
#define ENGINE_REFLECTABLECLASS_H

#include<vector>
#include"AssemblyRegistry.h"
#include<functional>
#include<type_traits>
#include<iostream>
#include<Shared/Core/Macros.h>
#include<Shared/Core/Logging.h>

namespace Refl {

    class Reflectable;

    struct ClassInfo;

    typedef Reflectable *(*constructionFunc)();

    struct ClassInfo {
        const char *m_name;
        const constructionFunc construct;
        const ClassInfo *const *const m_implements;
        const bool m_isVirtual;

        inline bool operator==(const ClassInfo &info) const {
            return m_name == info.m_name;
        }

        inline std::vector<const ClassInfo *> getImplementations() const {
            std::vector<const ClassInfo *> output = std::vector<const ClassInfo *>();

            const ClassInfo *const *ptr = m_implements;
            while (*ptr != nullptr) {
                output.push_back(*ptr);
                ptr++;
            }

            return output;
        }

        [[nodiscard]] inline bool isSubclassOf(const ClassInfo &info) const {
            if (*this == info)
                return true;

            if (getImplementations().empty())
                return false;
            return std::ranges::any_of(getImplementations(), [&](const ClassInfo *subclass) {
                return subclass->isSubclassOf(info);
            });
        }
    };

    template<typename t>
    class ClassRegistrationHelper {
    public:
        inline ClassRegistrationHelper() {
            getAssemblyRegistry()->m_registrationQueue.push([]() {
                CURRENTASSEMBLY()->m_info->m_classes.push_back(&t::classInfo);
            });
        }
    };

    class Reflectable {
    public:
        virtual const ClassInfo &getClassInfo() const = 0;

        virtual ~Reflectable() = default;
    };
}


#define VCLASS(name, baseclasses) \
    public:                          \
    static constexpr const char* VReflName = #name; \
    static constexpr const Refl::ClassInfo* VReflBaseclasses[] = baseclasses; \
    static constexpr bool VClassIsVirtual = false;                             \
    const Refl::ClassInfo& getClassInfo() const override; \
    static Refl::Reflectable* construct();\
    static inline Refl::ClassInfo classInfo = Refl::ClassInfo{VReflName, construct, VReflBaseclasses, VClassIsVirtual};

#define VABSTRACTCLASS(name, baseclasses) \
    public:                          \
    static constexpr const char* VReflName = #name; \
    static constexpr const Refl::ClassInfo* VReflBaseclasses[] = baseclasses; \
    static constexpr bool VClassIsVirtual = true;\
    const Refl::ClassInfo& getClassInfo() const override; \
    static Refl::Reflectable* construct();\
    static inline Refl::ClassInfo classInfo = Refl::ClassInfo{VReflName, construct, VReflBaseclasses, VClassIsVirtual};


#define REGISTERVCLASS(name) \
    static_assert(!std::is_abstract_v<name>); \
    static_assert(!name::VClassIsVirtual);\
    const ::Refl::ClassInfo& name::getClassInfo() const{ \
        return classInfo;\
    }                       \
    ::Refl::Reflectable* name::construct(){                 \
        return new name();                        \
    }                       \
    volatile static ::Refl::ClassRegistrationHelper<name> name##RegistrationHelper = ::Refl::ClassRegistrationHelper<name>();

#define REGISTERABSTRACTVCLASS(name) \
    static_assert(name::VClassIsVirtual);\
    const ::Refl::ClassInfo& name::getClassInfo() const{ \
        return classInfo;\
    }                       \
    ::Refl::Reflectable* name::construct(){              \
        return nullptr;                        \
    }                       \
    static volatile ::Refl::ClassRegistrationHelper<name> name##RegistrationHelper = ::Refl::ClassRegistrationHelper<name>();


#endif //ENGINE_REFLECTABLECLASS_H
