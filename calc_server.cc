#include <string>
#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "calcservice.grpc.pb.h"

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
  }

  Status Sub(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
  }

  Status Mul(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
  }

  Status Div(ServerContext *context, const CalcArgs *args, CalcResult *result) override
  {
    result->set_status(CalcResult_Status::CalcResult_Status_OK);
    //result->set_status(CalcResult_Status::CalcResult_Status_DBZ);
  }
};

void Serve()
{  
  CalcServiceImpl service;
  ServerBuilder builder;

  string bind = "127.0.0.1:62010";
  builder.AddListeningPort(bind, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  unique_ptr<Server> server(builder.BuildAndStart());
  cout << "Binded to " << bind << endl;
  server->Wait();
}

int main(int argc, char** argv)
{
  Serve();
  return 0;
}