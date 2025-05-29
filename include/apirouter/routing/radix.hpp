#ifndef API_ROUTER_ROUTING_RADIX_HPP_
#define API_ROUTER_ROUTING_RADIX_HPP_

#include "apirouter/generic/str_util.hpp"

#include <string>
#include <vector>
#include <optional>
namespace apirouter {
namespace radix {

class tree;

class node
{
public:
    node(const std::string& seg)
        : m_segment(seg), m_children{}
    {
    }

    node() : m_segment{}, m_children{} {}

    const std::string& get_segment() const { return m_segment; }

    const auto& get_children() const { return m_children; }

private:
    std::string m_segment;

    std::vector<node> m_children;

   

    friend bool operator==(const node&, const node&);
    friend class tree;
};
// TODO: NOT SCALEABLE
bool operator==(const radix::node& left, const radix::node& right)
{
    return (left.m_segment == right.m_segment);
}

///
/// @brief
///     Radix Trie
/// 
#pragma message ("!!!!!!!!!!!!!!REMEMBER TO OPTIMIZE THE RADIX::TREE!!!!!!!!!!!!!!!!")
class tree
{
public:
    tree() : m_root{}
    {
    }

    inline void insert(const std::vector<std::string>& list);
   
    inline void insert(node& entry, const generic::string_list& list);

    inline radix::node* search(const std::vector<std::string>& path);


private:

private:

    radix::node m_root;
};

void radix::tree::insert(
    const std::vector<std::string>& list
)
{
    return insert(m_root, list);
}

radix::node* radix::tree::search(const std::vector<std::string>& path)
{
    radix::node* head = &m_root;

    for (const auto& p : path)
    {
        auto iter = std::find(
            head->m_children.begin(),
            head->m_children.end(),
            p
        );

        if (iter == head->m_children.end())
            return nullptr;
        else {
            head = &(*iter);
        }
    }

    return head;
}

void radix::tree::insert(node& entry, const generic::string_list& list)
{
    radix::node* head = &entry;

    for (const auto& path : list)
    {
        auto iter = std::find(
            head->m_children.begin(),
            head->m_children.end(),
            path
        );

        if (iter != head->m_children.end())
        {
            head = iter._Ptr;
            continue;
        }
        else
        {
            head->m_children.push_back({ path });
            head = &head->m_children.back();
        }
    }
}

} // radix
} // apirouter


#endif // API_ROUTER_ROUTING_RADIX_HPP_