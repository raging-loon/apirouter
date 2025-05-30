#include <gtest/gtest.h>

#include <apirouter/generic/str_util.hpp>


TEST(GenericStrTest, SplitTest)
{
    std::string str = "192.168.0.1";
    std::vector<std::string> splitstr = { "192","168","0","1" };
    auto vec = apirouter::generic::split_to_str(str, '.');

    ASSERT_EQ(splitstr, vec);

    std::string str2 = "/wiki/edit/page/";
    std::vector<std::string> splitstr2{ "wiki","edit","page" };
    auto vec2 = apirouter::generic::split_to_str(str2, '/');

    ASSERT_EQ(splitstr2, vec2);


    auto vec3 = apirouter::generic::split_to_str("/wiki/edit/page", '/');

    ASSERT_EQ(splitstr2, vec3);
    auto vec4 = apirouter::generic::split_to_str("wiki/edit/page/", '/');
    ASSERT_EQ(splitstr2, vec4);

}
