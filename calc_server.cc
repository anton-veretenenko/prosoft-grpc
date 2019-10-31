#include <string>
#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "calcservice.grpc.pb.h"

#include "common.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using calcservice::CalcArgs;
using calcservice::CalcResult;
using calcservice::CalcService;
using calcservice::CalcResult_Status;

using namespace std;

class CalcServiceImpl final : public CalcService::Service
{
  Status Add(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
    result->set_result(args->arg1() + args->arg2());

    return Status::OK;
  }

  Status Sub(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
    result->set_result(args->arg1() - args->arg2());

    return Status::OK;
  }

  Status Mul(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
    result->set_result(args->arg1() * args->arg2());

    return Status::OK;
  }

  Status Div(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
    
    if (args->arg2() == 0) {
      result->set_status(CalcResult_Status::CalcResult_Status_DBZ);
      result->set_result(0);
    } else {
      result->set_result(args->arg1() / args->arg2());
    }

    return Status::OK;
  }
};

void Serve()
{  
  CalcServiceImpl service;
  ServerBuilder builder;

  builder.AddListeningPort(bind_addr, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Binded to " << bind_addr << endl;
  server->Wait();
}

int main(int argc, char** argv)
{
  Serve();
  return 0;
}