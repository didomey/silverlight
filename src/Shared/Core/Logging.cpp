#include"Logging.h"

namespace Log {
    void Log(LogInfo logMsg) {

        if (strlen(logMsg.m_sourceFile) == 0)
            volatile char a = *(volatile char *) nullptr;

        if (logMsg.m_severity != LogSeverity::Verbose || g_enableVerboseLogOut) {
            std::time_t time = std::chrono::system_clock::to_time_t(logMsg.m_logTime);
            std::tm *localtime = std::localtime(&time);
            std::stringstream output;
            output << "[" << toString(logMsg.m_severity) << "] "
                   << "{" << std::put_time(localtime, "%H:%M:%S") << "} "
                   << logMsg.m_message;

            if (logMsg.m_severity == LogSeverity::Crash) {
                output << " (" << logMsg.m_sourceFile << ":" << std::to_string(logMsg.m_lineNum) << ")";
            }

            if (logMsg.m_show) {
                nn::erreula::AppearArg errorArgs;

                errorArgs.errorArg.errorType = nn::erreula::ErrorType::Message;
                errorArgs.errorArg.renderTarget = nn::erreula::RenderTarget::Both;
                errorArgs.errorArg.controllerType = nn::erreula::ControllerType::DrcGamepad;
                errorArgs.errorArg.button1Label = u"ok";
                switch (logMsg.m_severity) {

                    case LogSeverity::Crash:
                        errorArgs.errorArg.errorTitle = u"The application has crashed!";
                        break;
                    case LogSeverity::Error:
                        errorArgs.errorArg.errorTitle = u"An error has occured!";
                        break;
                    case LogSeverity::Warning:
                        errorArgs.errorArg.errorTitle = u"Warning!";
                        break;
                    case LogSeverity::Info:
                        errorArgs.errorArg.errorTitle = u"Info";
                        break;
                    case LogSeverity::Verbose:
                        errorArgs.errorArg.errorTitle = u"Message";
                        break;
                }

                errorArgs.errorArg.errorMessage = logMsg.m_u16message;
                nn::erreula::AppearErrorViewer(errorArgs);
            }

            output << std::endl;

            std::string text = output.str();

            const char *cText = text.c_str();

            OSReport(cText);

            //Todo: Improve crash handeling by showing a message box before crashing on purpose.


            if (logMsg.m_severity == LogSeverity::Crash) {
                //Gives cemu time to write to finish writing to the log
                usleep(100);
                volatile char a = *(volatile char *) nullptr;
            }
        }
    }
}