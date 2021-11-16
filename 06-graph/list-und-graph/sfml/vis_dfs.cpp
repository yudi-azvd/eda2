#include <iostream>
// #include <fstream>
// #include <filesystem>
// #include <cstdlib>
// #include <map>

// using namespace std;
// using std::ifstream;

// #include <SFML/Graphics.hpp>
// #include <SFML/Window.hpp>

// #include "../matundgraph.h"

// struct Point
// {
//   int x, y;
// };


// vector<Edge> read_edges(string filename, int width, int height, vector<Point>& vertices) {
//   string base_path = "../../../resources/algs4-data/";
//   string full_path = base_path + filename;
//   ifstream infile;

//   infile.open(full_path.c_str(), ifstream::in);
//   if (!infile) {
//     cout << "not able to open: " << full_path << endl;
//     exit(1);
//   }

//   srand(32);
//   vector<Edge> edges;
//   int vertices_count, edges_count, v1, v2;
//   Point vertex;
//   infile >> vertices_count >> edges_count;
//   vertices.reserve(vertices_count);
//   edges.reserve(edges_count);
//   while (!infile.eof())
//   { 
//     infile >> v1 >> v2;
//     edges.push_back((Edge) {v1, v2});
//     vertex.x = rand() % (width);
//     vertex.y = rand() % (height);
//     vertices.push_back(vertex);
//     // assume que termina apenas com um \n depois do último número.
//   }
  
//   return edges;
// }

// void MatUndGraph_render_vertices(sf::RenderTarget& target, vector<Point>& vertices) {
//   int i, j;
//   sf::CircleShape circle;
//   // circle.setPosition(300, 200);
//   // circle.setFillColor(sf::Color::Red);
//   // circle.setRadius(8);
//   // target.draw(circle);
//   float radius = 1;
//   circle.setRadius(radius);
//   circle.setOrigin(sf::Vector2f(radius/2, radius/2));
//   circle.setFillColor(sf::Color(255, 255, 255));
//   for (i = 0; i < vertices.size(); ++i) {
//     circle.setPosition(vertices[i].x, vertices[i].y);
//     target.draw(circle);
//     // printf(">>> draw vertex %d\n", i);
//   }
// }

// void MatUndGraph_render_edges(sf::RenderTarget& target, MatUndGraph* g, vector<Point>& vertices) {
//   sf::VertexArray line(sf::LineStrip, 2);
//   line[0].position = sf::Vector2f(10, 0);
//   line[0].color = sf::Color(128, 128, 128);
//   line[1].position = sf::Vector2f(20, 0);

//   for (size_t i = 0; i < g->vertices; i++)
//   {
//     for (size_t j = 0; j < g->vertices; j++)
//     {
//       if (g->matrix[i][j] == 1) {
//         line[0].position = sf::Vector2f(vertices[i].x, vertices[i].y);
//         line[1].position = sf::Vector2f(vertices[j].x, vertices[j].y);
//         target.draw(line);
//       }
//     }
//   }

//   target.draw(line);
// }

// int main() {
//   sf::RenderWindow window;
//   window.create(sf::VideoMode(600, 400), 
//     "Graphs", sf::Style::Close | sf::Style::Titlebar);
//   window.setPosition(sf::Vector2i(0, 0));
//   window.setFramerateLimit(60);
  
//   vector<Point> vertices;
//   vector<Edge> edges = read_edges("mediumG.txt", 600, 400, vertices);
//   Edge edge;

//   printf("(%d, %d)\n", vertices[0].x, vertices[0].y);

//   MatUndGraph* g = MatUndGraph_create(vertices.size());

//   int i = 0;
//   while (window.isOpen())
//   {
//     sf::Event event;
//     while (window.pollEvent(event))
//     {
//       if (event.type == sf::Event::Closed)  
//         window.close();
//     }

//     window.clear();
//     MatUndGraph_render_edges(window, g, vertices);
//     MatUndGraph_render_vertices(window, vertices);
    
//     if (!edges.empty()) {
//       edge = edges.back();
//       edges.pop_back();
//       MatUndGraph_insert_edge(g, edge.a, edge.b);
//     }
    
//     window.display();
//   }
  
//   MatUndGraph_destroy(g);
//   return 0;
// }