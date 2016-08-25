#ifndef __CONFIG_H__
#define __CONFIG_H__

const int bufsize = 1024;

const char* bufstr[] = {
	"int io_setup(int maxevents, io_context_t *ctxp);\n",
	"int io_destroy(io_context_t ctx);\n",
	"int io_submit(io_context_t ctx, long nr, struct iocb *ios[]);\n",
	"int io_cancel(io_context_t ctx, struct iocb *iocb, struct io_event *evt);\n",
	"int io_getevents(io_context_t ctx_id, long min_nr, long nr, struct io_event *events, struct timespec *timeout);\n",
	"void io_set_callback(struct iocb *iocb, io_callback_t cb);\n",
	"void io_prep_pwrite(struct iocb *iocb, int fd, void *buf, size_t count, long long offset);\n",
	"void io_prep_pread(struct iocb *iocb, int fd, void *buf, size_t count, long long offset);\n",
	"void io_prep_pwritev(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset);\n",
	"void io_prep_preadv(struct iocb *iocb, int fd, const struct iovec *iov, int iovcnt, long long offset);\n"

};


























#endif
