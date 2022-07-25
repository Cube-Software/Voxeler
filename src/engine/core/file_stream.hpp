/*
    Fractal Engine - OpenGL 3D Game Engine
    Created by CubeSoftware
    Revised for Voxeler

    -------------------------------
    Copyright (c) 2021-2022 CubeSoftware
    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
    The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef FR_FILE_STREAM_HPP
#define FR_FILE_STREAM_HPP

#include "../fr.hpp"
#include "string.hpp"

namespace fr::core {
    class file_stream {
    public:
        enum
        {
            Writable,
            Readable
        };
    private:
        void open_handle_writable();
        void open_handle_readable();
    public:
        file_stream(const string& path, int type)
            : _type(type)
            , _load_path(path)
            , _handle(nullptr)
        {
            switch (_type)
            {
            case Writable:
                open_handle_writable();
                break;
            case Readable:
                open_handle_readable();
                break;
            }
        }

        ~file_stream()
        {
            if (_handle)
                _handle = nullptr;
        }

        file_stream& operator<<(const string& str)
        {
            write_string(str);
            return *this;
        }

        file_stream& operator<<(const char* str)
        {
            write_buffer(str);
            return *this;
        }

        file_stream& operator<<(char value)
        {
            write_char(value);
            return *this;
        }

        file_stream& operator>>(char& value)
        {
            read_char(value);
            return *this;
        }

        void close_file();
        void write_buffer(const void* buf, size_t bytes);

        void write_buffer(const char* buf)
        {
            write_buffer(buf, fr_strlen(buf));
        }

        void write_char(char value)
        {
            write_buffer(&value, 1);
        }

        void write_string(const string& str)
        {
            write_buffer(str.c_str(), str.Size());
        }

        void write_bytes(const frdeque<FRuchar>& bytes)
        {
            write_buffer(bytes.data(), bytes.size());
        }

        void read_buffer(void* buf, size_t size);

        void read_char(char& value)
        {
            read_buffer(&value, 1);
        }

        void read_all_file(string& str)
        {
            size_t bytes = get_size();
            str.Resize(bytes);
            read_buffer(str.Data(), bytes);
        }

        void read_bytes(frdeque<FRuchar>& dst)
        {
            size_t bytes = get_size();
            dst.Resize(bytes);
            read_buffer(dst.data(), bytes);
        }

        size_t get_size() const;
        size_t get_pos();
        void flushf();
        bool seekf(size_t pos);
        void* get_handle() const
        {
            return _handle;
        }

        string get_load_path() const
        {
            return _load_path;
        }

        int get_type() const
        {
            return _type;
        }

    private:
        string _load_path;
        void* _handle;
        int _type;
    };

    inline string read_file(const string& path)
    {
        string res;
        file_stream f(path, file_stream::Readable);
        f.read_all_file(res);
        return res;
    }

    inline frdeque<FRuchar> read_file_bytes(const string& path)
    {
        frdeque<FRuchar> res;
        file_stream f(path, file_stream::Readable);
        f.read_bytes(res);
        return res;
    }

    inline void write_all_file(const string& path, const string& src)
    {
        file_stream f(path, file_stream::Writable);
        f << src;
    }

    inline void write_all_file_bytes(const string& path, const frdeque<FRuchar>& src)
    {
        file_stream f(path, file_stream::Writable);
        f.write_bytes(src);
    }
}

#endif
