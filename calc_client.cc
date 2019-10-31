#include <string>
#include <iostream>
#include <memory>
#include <grpcpp/grpcpp.h>
#include "calcservice.grpc.pb.h"

#include "common.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using calcservice::CalcArgs;
using calcservice::CalcResult;
using calcservice::CalcService;
using calcservice::CalcResult_Status;

using namespace std;

class CalcClient
{
  public:
    CalcClient(shared_ptr<Channel> channel)
    {
      calc = CalcService::NewStub(channel);
    }

    double calculate(int64_t arg1, int64_t arg2, char op)
    {
      CalcArgs args;
      CalcResult result;
      ClientContext ctx;
      Status status;

      args.set_arg1(arg1);
      args.set_arg2(arg2);

      switch(op) {
        case '+':
          status = calc->Add(&ctx, args, &result);
          break;
        case '-':
          status = calc->Sub(&ctx, args, &result);
          break;
        case '*':
          status = calc->Mul(&ctx, args, &result);
          break;
        case '/':
          status = calc->Div(&ctx, args, &result);
          break;
        default:
          return 0; // ret 0 if unknown operation
          break;
      }

      if (status.ok()) {
        string msg;
        CalcResult_Status st = result.status();

        if (st == CalcResult_Status::CalcResult_Status_OK) {
          return result.result();
        } else
        if (st == CalcResult_Status::CalcResult_Status_ERR) {
          msg = "CalcService: error.";
        } else
        if (st == CalcResult_Status::CalcResult_Status_DBZ) {
          msg = "CalcService: division by zero error.";
        }

        cout << msg << endl;
      } else {
        cout << status.error_code() << ": " << status.error_message() << endl;
        return 0;
      }

      return 0; // by default
    }
  
  private:
    unique_ptr<CalcService::Stub> calc;

};

void print_usage()
{
  cout << "\nUsage: calc_client arg1 arg2 op\n" <<
          "\t- arg1, arg2 is a number\n" <<
          "\t- op is one of operations: +, -, *, /\n\n" <<
          "\tExamples:\n" <<
          "\t./calc_client 1 2 \\*\n" <<
          "\t./calc_client 1 2 +\n" << endl;
}

int main(int argc, char** argv)
{
  CalcClient client(grpc::CreateChannel(bind_addr, grpc::InsecureChannelCredentials()));

  char operations[] = "+-*/";

  if (argc < 4 || strlen(argv[3]) > 1 || strstr(operations, argv[3]) == NULL) {
    print_usage();
    return -1;
  }

  int64_t arg1, arg2;
  char op;

  arg1 = atoi(argv[1]);
  arg2 = atoi(argv[2]);
  op = argv[3][0];

  double result = client.calculate(arg1, arg2, op);

  cout << "\nResult: " << result << endl;

  return 0;
}