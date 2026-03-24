#include <memory>

namespace student_std {

template <typename T>
class binary_tree
{
public:
    using value_type = T;
    binary_tree(T const& val = T(), binary_tree* parent = nullptr) :
        m_value(val), m_parent(parent) {}
    binary_tree const* left() const { return m_left.get(); }
    binary_tree const* right() const { return m_right.get(); }
    binary_tree const* parent() const { return m_parent; }
    T const& value() const { return m_value; }
    void insert(T const& val = T()) {
        if(val < m_value) {
            if(m_left.get() == nullptr)
                m_left = std::make_unique<binary_tree>(val, this);
            else
                m_left->insert(val);
        }
        else {
            if(m_right.get() == nullptr)
                m_right = std::make_unique<binary_tree>(val, this);
            else
                m_right->insert(val);
        }        
    }
private:
    T m_value = T();
    std::unique_ptr<binary_tree> m_left = nullptr;
    std::unique_ptr<binary_tree> m_right = nullptr;
    binary_tree* m_parent = nullptr;
};

}