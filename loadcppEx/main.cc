/* #include "tensorflow/core/public/session.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/cc/ops/standard_ops.h"

using namespace tensorflow;
using namespace tensorflow::ops;
using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
 */
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atof */
#include <fstream>
#include <utility>
#include <vector>
//#include <math_ops.h>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include "tensorflow/cc/ops/const_op.h"
#include "tensorflow/cc/ops/image_ops.h"
#include "tensorflow/cc/ops/standard_ops.h"
#include "tensorflow/core/framework/graph.pb.h"
#include "tensorflow/core/framework/tensor.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/core/graph/graph_def_builder.h"
#include "tensorflow/core/lib/core/errors.h"
#include "tensorflow/core/lib/core/stringpiece.h"
#include "tensorflow/core/lib/core/threadpool.h"
#include "tensorflow/core/lib/io/path.h"
#include "tensorflow/core/lib/strings/stringprintf.h"
#include "tensorflow/core/platform/env.h"
#include "tensorflow/core/platform/init_main.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/types.h"
#include "tensorflow/core/public/session.h"
#include "tensorflow/core/util/command_line_flags.h"
//#include "tensorflow/cc/framework/cc/ops.h"

// These are all common classes it's handy to reference with no namespace.
using namespace tensorflow;
using namespace tensorflow::ops;
using tensorflow::Flag;
//using tensorflow::Tensor;
using tensorflow::Status;
using tensorflow::string;
using tensorflow::int32;


int main(int argc, char* argv[]) {
	
  clock_t tStrt;
  tStrt = clock(); 
  // Initialize a tensorflow session
  Scope root = Scope::NewRootScope();
  Session* session;
  Status status = NewSession(SessionOptions(), &session);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return -1;
  }

  // Read in the protobuf graph we exported
  //the graph folder must be relative to .exe
  GraphDef graph_def;
  status = ReadBinaryProto(Env::Default(), "C:/TFprocEx/input_graph.pb", &graph_def);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
	std::cout<<"Error 1"<<"\n";
    return -1;
  }

  // Add the graph to the session
  status = session->Create(graph_def);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return -1;
  }

  //create tensor object for appropriate dimension
  Tensor a(DT_FLOAT, TensorShape());
  a.scalar<float>()() = 4.0;
  
  Tensor b(DT_FLOAT, TensorShape());
  b.scalar<float>()() = 3.0;
  
  
  //assign input with graph variable
  std::vector<std::pair<string, tensorflow::Tensor>> inputs = {
    { "a", a }, { "b", b },
  };

  // The session will initialize the outputs
  std::vector<Tensor> outputs;

  // Run the session, evaluating our "Qval/BiasAdd" operation from the graph
  status = session->Run(inputs, {"c"}, {}, &outputs);
  if (!status.ok()) {
    std::cout << status.ToString() << "\n";
    return -1;
  } 
  auto output_c = outputs[0].flat<float>();
  std::cout <<"C is: "<<output_c(0)<< "\n";
    
  // Free any resources used by the session
  session->Close();
  clock_t tEnd;
  tEnd = clock();
  
  //std::cout<<"Load strt time: "<<((double)tStrt / CLOCKS_PER_SEC)<<" seconds. \n";
  std::cout<<"time taken to calc op : "<<((double)(tEnd-tStrt) / CLOCKS_PER_SEC)<<" seconds. \n";
	
  int idx = 99; 
  return idx;
}