#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

int ph_size(int fd){

	int size = 0;

	// cursor setting on the first position
	lseek(fd, 0, SEEK_SET);

	size = lseek(fd, 0, SEEK_END);

	// checking for errors
	if(size < 0){
		return errno;
	}

	// go to first position
	lseek(fd, 0, SEEK_SET);

	return size;
}


int log_size(int fd){

	// logical size = 0
	int l_size = 0, start = 0, end = 0;

	// setting cursor on the first position
	int pos = lseek(fd, 0, SEEK_SET);


	while(pos != lseek(fd, 0, SEEK_END)){

		// setting cursor on the nearest data
		pos = lseek(fd, 0, SEEK_DATA);

		// checking for errors
		if(pos < 0){
			return errno;
		}

		// saving the start of the data
		start = pos;

		// setting cursor on the nearest hole
		pos = lseek(fd, 0, SEEK_HOLE);

		// check for errors
		if(pos < 0){
			return errno;
		}

		// saving the end of the data
		end = pos;
		l_size = l_size + (end - start);
	}

	// bringing cursor on the first position
	lseek(fd, 0, SEEK_SET);

	return l_size;
}


int main(int argc, char **argv){

	// checking arguments
	if(argc < 3){
		std::cerr << "arguments are not enough" << std::endl;
		return 1;
	}

	// saving source and destination paths
	const char* source = argv[1];
	const char* destination = argv[2];

	// opening source path
	int source_fd = open(source, O_RDONLY);

	// checking for errors
	if(source_fd < 0){
		return errno;
	}

	std::cout<< ph_size(source_fd) << std::endl;
	std::cout<< log_size(source_fd) << std::endl;

	// opening destination path
	int destination_fd = open(destination, O_CREAT | O_TRUNC | O_WRONLY, 0644);

	// checking for errors
	if(destination_fd < 0){
		return errno;
	}


	char buffer[4096];

	while(true){

		int count = read(source_fd, buffer, 4096);

		if(count == 0){
			break;
		}

		if(count < 0){
			return 1;
		}

		int write_count = write(destination_fd, buffer, count);

		if(write_count < 0){
			exit(errno);
		}

	}

	 std::cout<< ph_size(destination_fd) << std::endl;
	 std::cout<< log_size(destination_fd) << std::endl;
	close(source_fd);

	close(destination_fd);

	return 0;
}
