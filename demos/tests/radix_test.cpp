#include <gtest/gtest.h>

#include <apirouter/routing/radix.hpp>

TEST(RadixTest, InsertAndSearch)
{
    apirouter::radix::tree test_tree{};

    test_tree.insert({ "hola", "mi", "amigo" });
    test_tree.insert({ "hola", "mis", "amigos" });
    test_tree.insert({ "privet", "moi", "tovarishsh" });

    ASSERT_TRUE(
        test_tree.search({ "privet", "moya", "podruga" }) == nullptr
    );
    auto* node = test_tree.search({ "hola", "mis" });
    ASSERT_TRUE(node);

    ASSERT_TRUE(node->get_children().size() == 1);

    test_tree.insert(*node, { "amigas" });

    ASSERT_TRUE(node->get_children().size() == 2);

    ASSERT_TRUE(
        test_tree.search({
            "hola", "mis", "amigas"
        })
    );
}