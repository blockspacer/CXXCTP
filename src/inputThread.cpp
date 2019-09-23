#include "inputThread.hpp"

#include "ClingInterpreterModule.hpp"
#include "utils.hpp"

namespace cxxctp {

[[ noreturn ]] void input_func()
{
    llvm::outs() << "main cling input thread... " << '\n';
    std::string command;
    std::string command_param1;
    std::string command_param2;
    while(true) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        std::cin >> command;
        llvm::outs() << "in main cling input thread: "<< command << '\n';
        if (command == "q") {
            //std::scoped_lock lock(m_runFlagMutex);
            //runFlag = false;
            break;
        } else if (command == "reload_all") {
            //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
            //reloadAllCling(); // NOTE: run under mutex
            cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([] {
                llvm::outs() << "dispatch reloadAllCling 2!... " << '\n';
                cling_utils::reloadAllCling();
            });
        }  else if (command == "reload_file") {
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch reload_file 1!... " << '\n';
                    cling::Interpreter::CompilationResult compilationResult;
                    cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1.c_str()]->metaProcessor_->process(".x " + command_param2, compilationResult, nullptr, true);
                });
            }
        } else if (command == "reload_module") {
            std::cin >> command_param1;
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                if(cling_utils::InterpreterModule::moduleToSources.find(command_param1)
                   != cling_utils::InterpreterModule::moduleToSources.end()) {
                    //removeClingModule(command_param1);
                    cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([command_param1] {
                        llvm::outs() << "dispatch reloadClingModule 1!... " << '\n';
                        cling_utils::reloadClingModule(command_param1,
                                          cling_utils::InterpreterModule::moduleToSources[command_param1]);
                    });
                } else {
                    llvm::outs() << "UNKNOWN MODULE! " << '\n';
                }
            }
        } else if (command == "unload") {
            unsigned int times = 1;
            std::cin >> command_param1 >> times;
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([command_param1, times] {
                    llvm::outs() << "dispatch unload 1!... " << '\n';
                    cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1]->interpreter_->unload(times);
                });
            }
        } else if (command == "process_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->
                  dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch process_code 1!... " << '\n';
                    cling_utils::processCode(*cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "execute_code") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->
                  dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch execute_code 1!... " << '\n';
                    cling_utils::executeCode(*cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1.c_str()]->interpreter_, command_param2);
                });
            }
        } else if (command == "declare") {
            std::cin >> command_param1;
            std::getline(std::cin, command_param1);
            llvm::outs() << "command_param: " << command_param1 << '\n';
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch declare 1!... " << '\n';
                    cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1.c_str()]->interpreter_->declare(command_param2);
                });
            }
        } else if (command == "execute_code_from_file") {
            /// note file must be without UTF BOM
            std::cin >> command_param1 >> command_param2;
            {
                //std::scoped_lock lock(InterpreterModule::interpMap["main_module"]->canRunMutex);
                cling_utils::InterpreterModule::receivedMessagesQueue_->dispatch([command_param1, command_param2] {
                    llvm::outs() << "dispatch execute_code_from_file 1!... " << '\n';
                    cling_utils::processCode(*cling_utils::InterpreterModule::InterpreterModule::interpMap[command_param1.c_str()]->interpreter_, cxxctp::utils::readWholeFile(command_param2));
                });
            }
        } else {
            llvm::outs() << "UNKNOWN COMMAND! " << '\n';
        }
    }

    llvm::outs() << "end input_func! " << '\n';
    std::terminate();
}

} // namespace cxxctp
