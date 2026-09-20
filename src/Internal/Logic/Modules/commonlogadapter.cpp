#include<Internal/Logic/modules.h>
#include<Game/Macros.h>

struct VariadicArray {
    uint8_t skip;
    uint8_t skipfloat;
    uint16_t aaa;
    uint32_t field3_0x4;
    uint32_t field4_0x8;
    uint32_t field5_0xc;
    uint32_t args_uint[8];
    double field7_0x30[8];
};

std::string NinSprintf(const char *text, VariadicArray *variadicArray) {
    std::stringstream textStream;
    while (*text != 0) {
        if (*text == '%') {
            text++;
            switch (*text) {
                case ('s'):
                    textStream << (char *) variadicArray->args_uint[variadicArray->skip];
                    variadicArray->skip += 1;
                    break;
                case ('d'):
                    textStream << (int32_t) variadicArray->args_uint[variadicArray->skip];
                    variadicArray->skip += 1;
                    break;
                default:
                    textStream << "*prcnt*";
                    textStream << std::string({*text});
                    return textStream.str();
            }
        }
        text++;
    }

    return textStream.str();
}

void
CommonLogReplace(uint32_t unk, const char *text, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5,
                 uint32_t p6) {
    static char textbuf[1000] = {0};

    sprintf(textbuf, text, p1, p2, p3, p4, p5, p6);

    CAFEINFO(textbuf)
}

void MainLogReplace(char **text) {
    CAFEINFO(*text);
}

using Printf1Signature = int (*)(char **text, uint32_t v1, uint32_t v2);

Printf1Signature printf1OgFunc = (Printf1Signature) 0x028f65f4;

int printf1Replace(char **text, uint32_t v1, uint32_t v2) {
    int a = printf1OgFunc(text, v1, v2);

    // fuck u
    //if (!std::string(*text).contains("BT0"))
        //CAFEINFO(*text);

    return a;
}


bool errorCallback(OSContext *context) {
    CAFEINFO("An exception occurred!");
    OSDumpContext(context);

    return true;

}

void logTest(uint32_t val) {
    CAFEINFO("0x0289e124: param_1 = " + toHexString(val));
}

FUNCBINDUNK(02d4f2ec, int(*)(uint32_t param_1, uint32_t param_2, ushort * param_3, unsigned char * param_4))

int repl_FUN_02d4f2ec(uint32_t param_1, uint32_t param_2, ushort *param_3, unsigned char *param_4) {
    int a = FUN_02d4f2ec(param_1, param_2, param_3, param_4);

    CAFEINFO((char *) param_1)

    return a;
}

FUNCBINDUNK(020097f0, void(*)(uint32_t param_1, char * text, char * PID))

void logPID(uint32_t param_1, char *text, char *PID) {
    CAFEINFO("PID: " + std::string(PID));

    FUN_020097f0(param_1, text, PID);
}

class CommonLogAdapter : Modules::PatchModule {
VCLASS(CommonLogAdapter, ESC({&Modules::PatchModule::classInfo, nullptr}))

private:
    CommonLogAdapter() {
        patch = {
                //{0x02c33614, DynamicFunctionReplacement((void *) CommonLogReplace, "stwu r1,-0x20(r1)", 0x028f65f4)},
                //{0x028f6554, DynamicFunctionReplacement((void *) CommonLogReplace, "or r12,r3,r3", 0x028f6554)},
                //{0x028c7a88, DynamicFunctionReplacement((void *) MainLogReplace, "blr", 0x028c7a88)},

                //{0x02860fd8, DynamicFunctionReplacement((void *) errorCallback, "mflr r0", 0x02860fd8)},
                //{0x0289e124, DynamicFunctionReplacement((void *) logTest, "blr", 0x0289e124)},
                //{0x028f6704, DynamicFunctionReplacementBL((void *) printf1Replace, (void *) printf1OgFunc, 0x028f6704)},
                //{0x02b55cbc, DynamicFunctionReplacementBL((void *) printf1Replace, (void *) FUN_02d4f2ec, 0x02b55cbc)},
                //{0x02009e40, DynamicFunctionReplacementBL((void *) logPID, (void *) FUN_020097f0, 0x02009e40)},
                //{0x02009e54, DynamicFunctionReplacementBL((void *) logPID, (void *) FUN_020097f0, 0x02009e54)},
        };
		this->disablePatch();
    }


    bool isCheatModule() override {
        return false;
    }
};

REGISTERVCLASS(CommonLogAdapter)
