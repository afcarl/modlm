#pragma once

#include <iostream>
#include <string>
#include <memory>

namespace cnn {
class Model;
struct RNNBuilder;
}

namespace lamtram {

class BuilderSpec {
public:
    BuilderSpec(const std::string & str);
    std::string type;
    int nodes, layers;
};
inline std::ostream & operator<<(std::ostream & out, const BuilderSpec & spec) {
    return out << spec.type << ":" << spec.nodes << ":" << spec.layers;
}

typedef std::shared_ptr<cnn::RNNBuilder> BuilderPtr;
class BuilderFactory {
public:
    static BuilderPtr CreateBuilder(const BuilderSpec & spec, int input_dim, cnn::Model & model);
};

}
