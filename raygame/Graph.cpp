#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include<raylib.h>

Graph::Graph(int width, int height, int nodeSize, int nodeSpacing)
{
	m_width = width;
	m_height = height;

	createGraph(nodeSize, nodeSpacing);
}

void Graph::draw()
{
	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->draw();
}

void Graph::update(float deltaTime)
{
	Actor::update(deltaTime);

	for (int i = 0; i < m_nodes.size(); i++)
		m_nodes[i]->update(deltaTime);
}

Node* Graph::checkList(std::deque<Node*> list, Node* lookingFor)
{
	for (int i = 0; i < list.size(); i++)
	{
		if (list[i] = lookingFor)
		{
			return lookingFor;
		}
	}
}

Node* Graph::getItem(std::deque<Node*> list, int slotNum)
{
	Node* itemPos = 0;
	for (int i = slotNum; i < list.size(); i++)
	{
		if (list[i] = itemPos)
		{
			return itemPos;
		}
		else
		return nullptr;
	}
}

void Graph::BFS(int startX, int startY, int goalX, int goalY)
{
	//Get a referance to the start and end nodes
	Node* start = getNode(startX, startY);
	Node* goal = getNode(goalX, goalY);

	//If the start or the end is null return
	if (!start || !goal)
		return;

	//Set the color to start and mark it as visited
	start->color = ColorToInt(GREEN);
	start->visited = true;

	//Set the iterator to be the start node
	Node* currentNode = start;

	//Create a queue to store the nodes
	std::deque<Node*> queue;
	//Add the start node to the queue
	queue.push_front(start);

	//Search for the goal while the queue isn't empty
	while (!queue.empty())
	{
		//Set the current node to be the first item in the queue
		currentNode = queue[0];
		//Remove the first item from the queue
		queue.pop_front();

		//Check if the iterator is the goal node
		if (currentNode == goal)
		{
			//Set the current node color to be yellow to mark it as found
			currentNode->color = ColorToInt(YELLOW);
			return;
		}

		//If the node wasn't the goal loop through its edges to get its neighbours
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a pointer to store the node at the end of the edge
			Node* currentEdgeEnd = nullptr;

			//Set the pointer to be the opposite end of the edge
			if (currentNode == currentNode->edges[i]->connectedNode2)
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			else
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

			//If the node at the opposite end hasn't been visited, mark it as visited and add it to the queue
			if (!currentEdgeEnd->visited)
			{
				currentEdgeEnd->color = ColorToInt(RED);
				currentEdgeEnd->visited = true;
				queue.push_back(currentEdgeEnd);
			}
		}
	}
}

void Graph::dijkstrap(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	Node* start = getNode(startX, startY);
	//Create a node pointer that points to the goal node
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
	{
		//return an empty list
		return;
		//end if statement
	}

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);
	start->gScore = 0;

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode;
	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list
	openList.push_front(start);

	//Loop while the open list is not empty
	while (!openList.empty())
	{
		//Sort the items in the open list by the g score
		bubbleSort(openList);

		//Set the iterator to be the first item in the open list
		currentNode = openList[0];

		//Check if the iterator is pointing to the goal node
		if (currentNode == goal)
		{
			//Mark the goal as being found by changing its color
			currentNode->color = ColorToInt(YELLOW);
			//Return the new path found
			return;

			//end if statement
		}
		Node* currentItem;

		//Pop the first item off the open list
		openList.pop_front();
		
		//Add the first item to the closed list
		closedList.push_front(currentItem);

		//Loop through all of the edges for the iterator
		for (int i = 0; i < currentNode->edges.size(); i++)
		{
			//Create a node pointer to store the other end of the edge
			Node* currentEdgeEnd = nullptr;

			//Check if the iterator is on the second end of the node
			if (currentNode == currentNode->edges[i]->connectedNode2)
			{
				//Set the edge end pointer to be the first end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode1;
			}
			//Otherwise if the iterator is on the first end of the node...
			else
			{
				//set the edge end pointer to be the second end of the node
				currentEdgeEnd = currentNode->edges[i]->connectedNode2;

				// end if statement
			}

			//Check if node at the end of the edge is in the closed list | WHAT DO I DO?! |
			if (checkList(closedList, currentEdgeEnd)) 
			{

				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				float currentGScore = currentNode->gScore + currentNode->edges[i]->cost;

				//Check if the node at the end of the edge is in the open list
				if (checkList(openList, currentEdgeEnd))
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);

					//Set the nodes g score to be the g score calculated earlier
					currentEdgeEnd->gScore = currentGScore;
					
					//Set the nodes previous to be the iterator
					currentEdgeEnd->edges[i]->connectedNode1 = currentEdgeEnd;

					//Add the node to the open list
					openList.push_back(currentEdgeEnd);

				}

				//Otherwise if the g score is less than the node at the end of the edge's g score...
				else
				{
					//Mark the node as visited by changing its color
					currentEdgeEnd->color = ColorToInt(RED);
					currentEdgeEnd->visited;

					//Set its g score to be the g score calculated earlier
					currentEdgeEnd->gScore = currentGScore;

					//Set its previous to be the current node
					currentEdgeEnd->edges[i]->connectedNode1 = currentNode;


				//end if statement
				}
			}
		}
		//end loop
	//end loop
	}
}

void Graph::aStar(int startX, int startY, int goalX, int goalY)
{
	//Create a node pointer that points to the start node
	Node* start = getNode(startX, startY);
	//Create a node pointer that points to the goal node
	Node* goal = getNode(goalX, goalY);

	//Check if the start or the goal pointer is null
	if (!start || !goal)
	{
		//return an empty list
		return;
		//end if statement
	}

	//Set the start nodes color to be green
	start->color = ColorToInt(GREEN);

	//Create a node pointer that will be act as an iterator for the graph
	Node* currentNode;
	//Create an open list
	std::deque<Node*> openList;
	//Create a closed list
	std::deque<Node*> closedList;

	//Add start to the open list

	//Loop while the open list is not empty

		//Sort the items in the open list by the f score

		//Set the iterator to be the first item in the open list

		//Check if the iterator is pointing to the goal node

			//Mark the goal as being found by changing its color
			//Return the new path found
	
		//end if statement

		//Pop the first item off the open list
		openList.pop_front();
		//Add the first item to the closed list
		closedList.pop_front();

		//Loop through all of the edges for the iterator

			//Create a node pointer to store the other end of the edge

			//Check if the iterator is on the second end of the node
				//Set the edge end pointer to be the first end of the node
			//Otherwise if the iterator is on the first end of the node...
				//set the edge end pointer to be the second end of the node
			// end if statement

			//Check if node at the end of the edge is in the closed list

				//Create a float and set it to be the g score of the iterator plus the cost of the edge
				//Create a float and set it to be the h score of the node at the end of the edge
				//Create a float for the f score and set it to be the g score combined with the h score

				//Check if the node at the end of the edge is in the open list

					//Mark the node as visited by changing its color
					//Set the nodes g score to be the g score calculated earlier
					//Set the nodes h score to be the h score calculated earlier
					//Set the nodes f score to be the f score calculated earlier
					//Set the nodes previous to be the iterator
					//Add the node to the open list

				//Otherwise if the f score is less than the node at the end of the edge's f score...

					//Mark the node as visited by changing its color
					//Set its g score to be the g score calculated earlier
					//Set the nodes h score to be the h score calculated earlier
					//Set its f score to be the f score calculated earlier
					//Set its previous to be the current node

				//end if statement
		//end loop
	//end loop
}

void Graph::bubbleSort(std::deque<Node*> node)
{
	for (int i = 0; i < node.size(); i++)
	{
		for (int j = node.size() - 1; j > i; j--)
		{
			if (node[j] < node[j - 1])
			{
				Node* temp = node[j];
				node[j] = node[j - 1];
				node[j - 1] = temp;
			}
		}
	}
}

Node* Graph::getNode(int xPos, int yPos)
{
	if (xPos < 0 || xPos > m_width || yPos < 0 || yPos > m_height)
	return nullptr;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->graphPosition == MathLibrary::Vector2(xPos, yPos))
			return m_nodes[i];
	}

	return nullptr;
}

void Graph::createGraph(int nodeSize, int nodeSpacing)
{
	float xPos = 0;
	float yPos = 0;

	//Loops for the amount of nodes in the graph
	for (int i = 0; i < m_width * m_height; i++)
	{
		//Create a new node with the current graph position and size
		Node* currentNode = new Node(xPos, yPos, nodeSize);

		//Set the local offset for spacing
		MathLibrary::Vector2 nodeLocalPosition = { xPos * nodeSpacing, yPos * nodeSpacing };
		currentNode->setLocalPosition(nodeLocalPosition);

		//Add the node as a child of the grid and update the list
		addChild(currentNode);
		m_nodes.push_back(currentNode);

		//Connect the node to all nodes in range
		for (int j = 0; j < m_nodes.size(); j++)
		{
			//Find the displacement between the current node being added and the node being evaluated
			MathLibrary::Vector2 displacement = m_nodes[j]->graphPosition - currentNode->graphPosition;

			//Checks if teh magnitude of the displacement is farther that the maximum 
			if (displacement.getMagnitude() <= 1.42f && displacement.getMagnitude() > 0)
			{
				//Create a new edge that connects the two nodes
				Edge* currentEdge = new Edge(m_nodes[j], currentNode);
				currentNode->edges.push_back(currentEdge);
				m_nodes[j]->edges.push_back(currentEdge);
			}
		}

		//Increase the graph position on the x
		xPos++;
		
		//If the x position is greater than the width, reset it to 0 and increase the y
		if (xPos >= m_width)
		{
			xPos = 0;
			yPos++;
		}
	}
}
