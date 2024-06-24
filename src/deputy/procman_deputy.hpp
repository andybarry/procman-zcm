#ifndef PROCMAN_PROCMAN_DEPUTY_HPP__
#define PROCMAN_PROCMAN_DEPUTY_HPP__

#include <set>
#include <string>

#include <zcm/zcm-cpp.hpp>

#include <zcmtypes/procman_zcm/orders_t.hpp>
#include <zcmtypes/procman_zcm/discovery_t.hpp>
#include <zcmtypes/procman_zcm/deputy_info_t.hpp>
#include <zcmtypes/procman_zcm/output_t.hpp>

#include "event_loop.hpp"
#include "procman/procman.hpp"

namespace procman {

struct DeputyCommand;

struct DeputyOptions {
  static DeputyOptions Defaults();

  std::string deputy_id;
  std::string zcm_url;
  bool verbose;
};

class ProcmanDeputy {
  public:
    ProcmanDeputy(const DeputyOptions& options);
    ~ProcmanDeputy();

    void Run();

  private:
    void OrdersReceived(const zcm::ReceiveBuffer* rbuf, const std::string& channel,
        const procman_zcm::orders_t* orders);
    void DiscoveryReceived(const zcm::ReceiveBuffer* rbuf,
        const std::string& channel, const procman_zcm::discovery_t* msg);
    void InfoReceived(const zcm::ReceiveBuffer* rbuf,
        const std::string& channel, const procman_zcm::deputy_info_t* msg);

    void OnDiscoveryTimer();

    void OnOneSecondTimer();

    void OnIntrospectionTimer();

    void OnQuitTimer();

    void OnPosixSignal(int signum);

    void OnProcessOutputAvailable(DeputyCommand* mi);

    void UpdateCpuTimes();

    void CheckForStoppedCommands();

    void TransmitProcessInfo();

    void MaybeScheduleRespawn(DeputyCommand *mi);

    int StartCommand(DeputyCommand* mi, int desired_runid);

    int StopCommand(DeputyCommand* mi);

    void TransmitStr(const std::string& command_id, const char* str);

    void PrintfAndTransmit(const std::string& command_id, const char *fmt, ...);

    void MaybePublishOutputMessage();

    DeputyOptions options_;

    Procman* pm_;

    zcm::ZCM* zcm_;

    EventLoop event_loop_;

    std::string deputy_id_;

    SystemInfo cpu_time_[2];
    float cpu_load_;

    int64_t deputy_start_time_;
    pid_t deputy_pid_;

    zcm::Subscription* discovery_sub_;
    zcm::Subscription* info_sub_;
    zcm::Subscription* orders_sub_;

    TimerPtr discovery_timer_;
    TimerPtr one_second_timer_;
    TimerPtr introspection_timer_;
    TimerPtr quit_timer_;
    TimerPtr check_output_msg_timer_;

    SocketNotifierPtr zcm_notifier_;

    std::map<ProcmanCommandPtr, DeputyCommand*> commands_;

    bool exiting_;

    int64_t last_output_transmit_utime_;
    int output_buf_size_;
    procman_zcm::output_t output_msg_;
};

}  // namespace procman

#endif  // PROCMAN_PROCMAN_DEPUTY_HPP__
