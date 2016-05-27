#define DEVICE_NAME "tiny"
#define DEVICE_PATH "/dev/" DEVICE_NAME
#define MAGIC_NO '4'
#define IOCTL_CMD _IOR(MAGIC_NO, 0, char *)

static int major_no;
