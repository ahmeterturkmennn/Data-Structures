#include "graph.hpp"
#include "memory.hpp"

Graph::Vertex::Vertex(size_t id) : m_id(id), m_color(0) { }

size_t Graph::Vertex::id() const
{
    return m_id;
}

int Graph::Vertex::color() const
{
    return m_color;
}

bool Graph::Vertex::color(int color)
{
    if (color == 0) {
        this->m_color = 0;
        return true;
    }
    for (List<Vertex*>::Iterator iter = this->m_neighbors.begin() ; iter != this->m_neighbors.end() ; ++iter) {
        if ((*iter)->m_color==color){
            return false;
        }

    }
    this->m_color=color;
    return true;
}

void Graph::Vertex::add_neighbor(Vertex* other)
{
    if (!other) {
        return;
    }
     for (List<Vertex*>::Iterator iter = this->m_neighbors.begin() ; iter != this->m_neighbors.end() ; ++iter) {
        if (*iter==other){
            return;
        }
    }
    this->m_neighbors.push_back(other);
    other->m_neighbors.push_back(this);

}


void Graph::Vertex::remove_neighbor(Vertex* other)
{
    if (!other) {
        return;
    }
    for (List<Vertex*>::Iterator iter = m_neighbors.begin(); iter != m_neighbors.end(); ++iter) {
        if (*iter == other) {
            m_neighbors.remove(iter);
            break;
        }
    }
    for (List<Vertex*>::Iterator iter = other->m_neighbors.begin(); iter != other->m_neighbors.end(); ++iter) {
        if (*iter == this) {
            other->m_neighbors.remove(iter);
            break;
        }
    }
}

Graph::Graph() { }

Graph::~Graph()
{
    for (List<Vertex*>::Iterator iter = this->m_vertices.begin() ; iter != this->m_vertices.end() ; ++iter) {
        delete *iter;
    }
    while (m_vertices.begin() != m_vertices.end()) {
        m_vertices.remove(m_vertices.begin());
    }
}


Graph::Graph(const Graph &other) :m_vertices(){
     for (List<Vertex*>::ConstIterator iter = other.m_vertices.begin(); iter != other.m_vertices.end(); ++iter) {
        m_vertices.push_back(*iter);
    }
}

Graph::Graph(Graph &&other) : m_vertices()
{
    for (List<Vertex*>::Iterator iter = other.m_vertices.begin(); iter != other.m_vertices.end(); ++iter) {
        m_vertices.push_back(*iter);
    }
    while (other.m_vertices.begin() != other.m_vertices.end()) {
        other.m_vertices.remove(other.m_vertices.begin()); // Remove from the source
    }
}
Graph &Graph::operator=(const Graph &other) {
    if (this != &other) {
        for (List<Vertex*>::Iterator iter = m_vertices.begin(); iter != m_vertices.end(); ++iter) {
            delete *iter;
        }
        while (m_vertices.begin() != m_vertices.end()) {
            m_vertices.remove(m_vertices.begin());
        }
        for (List<Vertex*>::ConstIterator iter = other.m_vertices.begin(); iter != other.m_vertices.end(); ++iter) {
            m_vertices.push_back(*iter);
        }
    }
    return *this;
}





Graph& Graph::operator=(Graph &&other)
{
    if (this != &other) {
        for (List<Vertex*>::Iterator iter = m_vertices.begin(); iter != m_vertices.end(); ++iter) {
            delete *iter;
        }
        while (m_vertices.begin() != m_vertices.end()) {
            m_vertices.remove(m_vertices.begin());
        }
        for (List<Vertex*>::Iterator iter = other.m_vertices.begin(); iter != other.m_vertices.end(); ++iter) {
            m_vertices.push_back(*iter);
        }
        while (other.m_vertices.begin() != other.m_vertices.end()) {
            other.m_vertices.remove(other.m_vertices.begin());
        }
    }
    return *this;
}

size_t Graph::add_vertex()
{

    Vertex* vertex = new Vertex(m_vertices.size()+1);
    m_vertices.push_back(vertex);
    return vertex->id();
}

Graph::Vertex* Graph::operator[](size_t id)
{
    for (List<Vertex*>::Iterator iter = m_vertices.begin() ; iter != m_vertices.end() ; ++iter) {
        if ((*iter)->id()==id){
            return *iter;//?pointer or *iter
        }
    }
    throw std::domain_error("Vertex with the given ID does not exist.");
}



void Graph::connect(size_t id1, size_t id2)
{
    Vertex* v1 = (*this)[id1];
    Vertex* v2 = (*this)[id2];
    if (v1 && v2) {
        v1->add_neighbor(v2);
    }
}
int Graph::max_color() const {
    return 9;
}
bool Graph::color_helper(List<Vertex*>::Iterator vertex)
{
    //If the vertices are depleted, return true
    if (vertex == m_vertices.end()) {
        return true;
    }

     if ((*vertex)->color() != 0) {//if this vertex is colored
        return color_helper(++vertex);//skip to next one
    }else{//vertex not colored
        for (int currentColor = 1; currentColor <= max_color(); ++currentColor) {//check all the colors
            for (List<Vertex*>::Iterator it = (*vertex)->m_neighbors.begin(); it != (*vertex)->m_neighbors.end(); ++it) {
                if ((*it)->color() == currentColor) {//if neighbor has that color, break and move to next color
                    break;
                }
            }
            if ((*vertex)->color(currentColor)) {//if vertex is colored with current color
                List<Vertex*>::Iterator temp = vertex;

                if (color_helper(++temp)) {
                    return true;// Successfully colored all vertices
                }
                // Backtrack: reset the color if the current color doesn't work
                (*vertex)->color(0);
            }
        }
    }
    // If no valid color can be assigned, return false to trigger backtracking
    return false;
}


bool Graph::color()
{
    for (List<Vertex*>::Iterator iter = m_vertices.begin(); iter != m_vertices.end(); ++iter)
    {
        if ((*iter)->color() == 0)//not colored
        {
            if (!color_helper(iter))
            {
                return false;
            }
        }
    }
    return true;
}
