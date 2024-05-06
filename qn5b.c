#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main() {
    char fname[30], ch;
    int fd1, fd2, n, ret;
    struct stat st;
    printf("Enter filename: ");
    scanf("%s", fname);
    fd1 = open(fname, O_RDONLY);
    if (fd1 < 0) {
        printf("File not found\n");
        return 1;
    }
    fd2 = open("file.out", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    while ((n = read(fd1, &ch, 1)) > 0) {
        ch = (ch >= 'a' && ch <= 'z') ? ch - 32 : ch;
        write(fd2, &ch, 1);
    }
    ret = fstat(fd1, &st);
    if (ret == 0) {
        printf("File size = %ld byte\n", st.st_size);
    }
    close(fd1);
    close(fd2);
    return 0;
}

