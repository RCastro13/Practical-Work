# Description:

- TP1 assignment was to return the number of faces of a planar graph.
The input was a planar graph

- TP2 had 4 tasks to complete:
Find the minimun path (distance) from vertex 0 to every other vertex and which year that would be possible;
Find the first year all vertices could be reacheable starting from vertex 0;
Find the path with the least cost that includes all vertices;
The input was a connected graph with the edges having 3 weights.

- TP3 assignment was to use dinamic programming to solve the following problem:
Given a set of section with the attributes: time to finish the section and multiplier bonus, and the set of tricks with the attributes: time to finish a trick
and points for doing the trick, what's the best combination os tricks I have to do in each section so I have a maximum score in the end;
The points in a section are calculated by: X * r * M, where X is the somatorial of points of all tricks made in the section, r is the number of tricks made in the section
and M is multiplier bonus of the section.
The last rule is that if a trick is done in a section, if you do the same one in the next section, you would only get floor(P/2) points (P is the trick score) by doing that trick;
The input was a set of tricks and sections.