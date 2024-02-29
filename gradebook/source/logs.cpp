#include <glog/logging.h>

int main(int argc, char *argv[])
{
	google::InitGoogleLogging(argv);

	// Log messages at different severity levels
	LOG(INFO) << "This is an informational message.";
	LOG(WARNING) << "This is a warning message.";
	LOG(ERROR) << "This is an error message.";

	return 0;
}