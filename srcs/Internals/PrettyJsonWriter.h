#pragma once

#include "JsonWriter.h"
#include "IndentedPrint.h"

using namespace ArduinoJson::Generator;

class PrettyJsonWriter : public JsonWriter
{
public:
    explicit PrettyJsonWriter(IndentedPrint& sink)
        : JsonWriter(sink), _indenter(sink)
    {
    }

    virtual void beginArray()
    {
        _length += _sink.write('[');
        _indenter.indent();
        _length += _indenter.println();
    }

    virtual void endArray()
    {
        _length += _indenter.println();
        _indenter.unindent();
        _length += _sink.write(']');
    }

    virtual void writeColon()
    {
        _length += _sink.print(": ");
    }

    virtual void writeComma()
    {
        _length += _sink.write(',');
        _length += _indenter.println();
    }

    virtual void beginObject()
    {
        _length += _sink.write('{');
    }

    virtual void endObject()
    {
        _length += _sink.write('}');
        _indenter.unindent();
    }

private:
    IndentedPrint& _indenter;
};
