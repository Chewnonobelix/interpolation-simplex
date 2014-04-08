#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>
#include <iostream>

template<class T>
class Tree
{
private:
    T m_data;
    std::vector<Tree<T>> m_children;

public:
    Tree() {}
    Tree(const Tree<T>& t): m_data(t.data()), m_children(t.m_children)
    {}
    Tree(const T& data): m_data(data)
    {}

    bool hasChild() const
    {
        return !m_children.empty();
    }

    std::vector<Tree<T>> children() const
    {
        return m_children;
    }

    int nbChild() const
    {
        return m_children.size();
    }

    T data() const
    {
        return m_data;
    }

    void setData(T data)
    {
        m_data = data;
    }

    bool contain(const T& data) const
    {
        if(m_data == data)
        {
            return true;
        }
        else if(!hasChild())
        {
            return false;
        }
        else
        {
            bool ret = false;
            for(int i = 0; i < nbChild(); i ++)
            {
                ret |= m_children[i].contain(data);
            }

            return ret;
        }
    }

    int nbLeaf() const
    {
        if(!hasChild())
        {
            return 1;
        }
        else
        {
            int ret = 0;
            for(int i = 0; i < nbChild(); i ++)
            {
                ret += m_children[i].nbLeaf();
            }

            return ret;
        }
    }

    void setChild(int index, const Tree<T>& child)
    {
        if(index >= nbChild())
        {
            m_children.push_back(child);
        }
        else
        {
            m_children[index] = child;
        }
    }

    void addChild(int index, const Tree<T>& child)
    {
        if(index >= nbChild())
        {
            m_children.push_back(child);
        }
        else
        {
            m_children.insert(m_children.begin() + index , child);
        }
    }

    Tree<T>& operator()(int index)
    {
        if(index >= 0 && index < nbChild())
        {
            return m_children[index];
        }

        throw std::string("Out of range");
    }

    Tree<T> operator()(int index) const
    {
        if(index >= 0 && index < nbChild())
        {
            return m_children[index];
        }

        throw std::string("Out of range");
    }

    Tree<T>& operator()(const T& data)
    {
        if(!contain(data))
        {
            throw std::string("Don't contain data");
        }

        if(m_data == data)
        {
            return *this;
        }
        else
        {
            for(int i = 0; i < nbChild(); i ++)
            {
                if((*this)(i).contain(data))
                {
                    return m_children[i];
                }
            }
        }
    }

    Tree<T>& operator = (const Tree<T>& t)
    {
        m_children.clear();

        m_data = t.data();
        m_children = t.children();

        return *this;
    }

    int nbElement() const
    {
        int ret = 0;
        for(int i = 0; i < nbChild(); i ++)
        {
            ret += m_children[i].nbElement();
        }

        return ret + 1;
    }
    const Tree<T>& operator()(const T& data) const
    {
        if(!contain(data))
        {
            throw std::string("Don't contain data");
        }

        if(m_data == data)
        {
            return *this;
        }
        else
        {
            for(int i = 0; i < nbChild(); i ++)
            {
                if((*this)(i).contain(data))
                {
                    return m_children[i];
                }
            }
        }
    }
};

#endif // TREE_H
