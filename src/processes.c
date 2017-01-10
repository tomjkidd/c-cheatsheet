#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void error(char *msg) {
  fprintf(stderr, "%s: %s\n", msg, strerror(errno));
  exit(1);
}

void redirect_file_descriptor(int file_descriptor_from, int file_descriptor_to) {
  if(dup2(file_descriptor_to, file_descriptor_from) == -1)
    error("Can't redirect output");
}

int get_file_descriptor(FILE *f) {
  return fileno(f);
}

int test_simple() {
  printf("Process start\n");
  pid_t p = getpid();
  printf("Process Id: %i\n", p);
  
  printf("About to fork...");
  pid_t pid = fork();

  if(pid == -1) {
    fprintf(stderr, "Fork failed: %s\n", strerror(errno));
    return 1;
  }

  if(pid == 0) {
    printf("In simple child process\n");
    return 0; // Return 0 to indicate successful finish of child task
  } else {
    printf("In main process\n");
  }
  
  printf("This should only print in the parent process\n");

  int status;
  waitpid(pid, &status, 0);

  printf("Simple child finished\n");
  return status;
}

int test_exec() {
  pid_t pid = fork();
  
  if(pid == (pid_t) -1) {
    fprintf(stderr, "Fork 2 failed: %s\n", strerror(errno));
    return 1;
  }

  if(pid == (pid_t) 0) {
    printf("About to launch exec command\n");

    /* call out to the shell to run one of the other programs from this one on the child process */
    if(execl("./formatting", "./formatting", NULL) == -1) {
      fprintf(stderr, "Cannot run program: %s\n", strerror(errno));
    }
    printf("This should not be printed because exec will not return...");
    return 0;
  } else {
    printf("In main process, again\n");
  }

  printf("This also should only print in the parent process, wait for children\n");

  int status;
  waitpid(pid, &status, 0);

  return status;
}

int test_redirect_of_stdout_to_file() {
  FILE *f = fopen("process-output.txt", "w");
  
  // Create a child process
  pid_t pid = fork();
  
  if (pid == (pid_t) -1) {
    error("Can't fork process");
  }

  if (pid == (pid_t) 0) {
    printf("Changing child to write to process-output.txt\n");
    redirect_file_descriptor(get_file_descriptor(stdout), get_file_descriptor(f));
    printf("This should show up in the file, not on stdout\n");
    redirect_file_descriptor(get_file_descriptor(f), 1);
    if (fclose(f) == -1) {
      error("Unable to close process-output.txt");
    };
    return 0;
  }

  printf("The main process should get here, not the child\n");

  int status;
  waitpid(pid, &status, 0);
  
  return status;
}

int test_write_from_child_to_parent() {
  int fd[2]; // fd[0] is the read end of the pipe, fd[1] is the write end of the pipe
  if (pipe(fd) == -1) {
    error("Can't create pipe\n");
  }

  int read_fd = fd[0];
  int write_fd = fd[1];

  pid_t pid = fork();

  if (pid == (pid_t) -1) {
    error("Can't fork process");
  }

  if (pid == (pid_t) 0) {
    printf("Child changed stdout to write to pipe\n");
    redirect_file_descriptor(get_file_descriptor(stdout), write_fd);
    close(read_fd); // Child will not use the read end of the pipe
    printf("This should show up in the main thread\n");
    printf("This should also show up in the main thrread\n");
    return 0;
  }

  printf("Parent changed stdin to read from pipe\n");
  redirect_file_descriptor(get_file_descriptor(stdin), read_fd);
  close(write_fd); // Parent will not use the write end of the pipe

  int status;
  waitpid(pid, &status, 0);
  
  char line[255];
  while (fgets(line, 255, stdin)) {
    printf("line detected from child: %s", line);
  }
  
  return status;
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    test_write_from_child_to_parent();
  } else {
    int to_run = atoi(argv[1]);

    switch (to_run) {
    case 0:
      test_simple();
      break;
    case 1:
      test_exec();
      break;
    case 2:
      test_redirect_of_stdout_to_file();
      break;
    case 3:
      test_write_from_child_to_parent();
      break;
    default:
      test_write_from_child_to_parent();
    }
  }

  return 0;
}

/* ANALYSIS:
 One of the fun things to note is that '<', '>', '2>', and '|' from the command line corresponde to C functionality

 * '<' is a redirect of stdin
 * '>' is a redirect of stdout
 * '2>' is a redirect of stderr
 * '|' is a simple way to link one programs stdin to anothers stdout

 The file descriptor table is where these redirections are carried out.

 |stream | file descriptor|
 |---|---|
 | stdin  | 0 |
 | stdout | 1 |
 | stderr | 2 |
*/
