#pragma once
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <cstring>

struct log_t {

  static log_t *log;

  log_t(const char *path) : _path(path), _fd(nullptr) {}

  static void init(const char *name) {
    if (!log) {
      log = new log_t(name);
    }
  }

  static log_t &inst() {
    assert(log);
    return *log;
  }

  void printf(const char *fmt, ...) {
    va_list ap;
    {
      va_start(ap, fmt);
      _open_fd();
      if (_fd) {
        vfprintf(_fd, fmt, ap);
        fflush(_fd);
      }
      va_end(ap);
    }
  }

protected:
  void log_t::_open_fd() {
    if (!_fd) {
      _fd = fopen(_path, "w");
    }
  }

  const char *_path;
  FILE *_fd;
};
