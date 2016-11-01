
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <dynet/model.h>
#include <dynet/rnn.h>
#include <dynet/lstm.h>
#include <dynet/gru.h>
#include <modlm/builder-factory.h>
#include <modlm/macros.h>
#include <modlm/ff-builder.h>

using namespace std;
using namespace modlm;

BuilderSpec::BuilderSpec(const std::string & spec) {
    vector<string> strs;
    boost::algorithm::split(strs, spec, boost::is_any_of(":"));
    if(strs.size() != 3)
        THROW_ERROR("Invalid layer specification \"" << spec << "\", must be layer type (ff/rnn/lstm/gru), number of nodes, number of layers, with the three elements separated by a token.");
    type = strs[0];
    nodes = boost::lexical_cast<int>(strs[1]); 
    layers = boost::lexical_cast<int>(strs[2]); 
}

BuilderPtr BuilderFactory::CreateBuilder(const BuilderSpec & spec, int input_dim, dynet::Model & model) {
    // cerr << "BuilderFactor::CreateBuilder(" << spec << ", " << input_dim << ", " << (long)&model << ")" << endl;
    if(spec.type == "ff") {
        return BuilderPtr(new dynet::FFBuilder(spec.layers, input_dim, spec.nodes, &model));
    } else if(spec.type == "rnn") {
        return BuilderPtr(new dynet::SimpleRNNBuilder(spec.layers, input_dim, spec.nodes, &model));
    } else if(spec.type == "lstm") {
        return BuilderPtr(new dynet::LSTMBuilder(spec.layers, input_dim, spec.nodes, &model));
    } else if(spec.type == "gru") {
        THROW_ERROR("GRU spec.nodes are not supported yet.");
        // return BuilderPtr(new dynet::GRUBuilder(spec.layers, input_dim, spec.nodes, &model));
    } else {
        THROW_ERROR("Unknown layer type " << spec.type);
    }
}
