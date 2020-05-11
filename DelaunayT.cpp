#include "DelaunayT.h"

//Constructor
DelaunayT::DelaunayT() {
	Triangulation = new RedBlueTree<Triangle>; //empty tree
	PointsToFix = NULL;
	maxX = maxY = -10000000;
	minX = minY =  10000000;
}

//Deconstructor
DelaunayT::~DelaunayT() {

	DeleteTriangulation();

	if (Triangulation)
		delete Triangulation;
	if (PointsToFix)
		delete PointsToFix;
}

//add a triangle to the tree
void DelaunayT::Insert(Triangle* newtri) {
	if (newtri->GetMaxX() > maxX)
		maxX = newtri->GetMaxX();
	if(newtri->GetMaxY() > maxY)
		maxY = newtri->GetMaxY();
	if (newtri->GetMinX() < minX)
		minX = newtri->GetMinX();
	if (newtri->GetMinY() < minY)
		minY = newtri->GetMinY();

	Triangulation->Insert(newtri);
}

//add a point to the triangulation-Start
void DelaunayT::Insert(Vertex* newvert) {
	/*
	1. Find all illegal triangles
		Add to a copy of that triangle to list
		Add a copy of their points to a list
		delete all illegal triangles from the Triangulation, and the list of illegal triangles

		Redraw with the list of points
	*/
	if (newvert->X < minX)
		minX = newvert->X;
	else if (newvert->X > maxX)
		maxX = newvert->X;

	if (newvert->Y < minY)
		minY = newvert->Y;
	else if (newvert->X > maxY)
		maxY = newvert->Y;

	std::cout << "NEW VERTICE: " << *newvert << std::endl;

	if (Triangulation) {
		if (PointsToFix == NULL)
			PointsToFix = new LinkedList<Vertex>;

		TreeNode<Triangle>* temp = Triangulation->Root;

		
		if (temp != Triangulation->NIL)
			GetIllegals(temp, newvert);
		
		//Search Phase 1 complete.
		//----------------------------------------------------------------------------------------------
		//Phase 2: delete illicit triangles from tree

		std::cout << IllegalTriangles.size() << " illegal trianlges found" << std::endl;
		int violationnum = IllegalTriangles.size(); //number of illegal triangles found- save for fixingn cases

		if (PointsToFix) {
		
			//delete all illegal triangles from the tree
			while (IllegalTriangles.size() > 0) {
				std::cout << MAGENTA << IllegalTriangles.front() << DEFAULT << std::endl;
				Triangulation->Delete(&IllegalTriangles.front());
				IllegalTriangles.pop_front();
			}

	//Remove Phase 2 complete.
	//----------------------------------------------------------------------------------------------
	//Phase 3: draw/redraw
		//CASE 1: No Violations found
			//No violations were found
			//get the closet triangle, compare both versions of the spiltting on the new quadrilateral
			//remove the triangle if needed and add the two new triangulations
			if (violationnum == 0) {
				std::cout << YELLOW << "No Violations" << DEFAULT << std::endl;
				Triangle closest = GetClosestStart(newvert); //a pointer in the tree- not independent value
				//closet + newvert split in half in some form are the two new triangles. 
				//then delete closest from the tree. and insert the two new triangles
				//want to maximize the minimum angle
				//int starttreesize = Triangulation->Nodenum;
			/*	Triangle secondclosest;
				if (starttreesize > 1) {
					secondclosest = GetSecondClosestStart(newvert);
					std::cout << "second closest: " << secondclosest;
				}
			*/
				
				//Pair1A = closest;
				Triangle Pair1B(*newvert, closest.GetClosest(newvert), closest.GetMiddle(newvert));
				float Pair1MinAngleA = closest.GetMinAngle();
				float Pair1MinAngleB = Pair1B.GetMinAngle();

				float ComparePair1 = (Pair1MinAngleA < Pair1MinAngleB) ? Pair1MinAngleA : Pair1MinAngleB; //take the smaller of the two

				Triangle Pair2A(*newvert, closest.GetClosest(newvert), closest.GetFurthest(newvert));
				Triangle Pair2B(*newvert, closest.GetMiddle(newvert), closest.GetFurthest(newvert));

				float Pair2MinAngleA = Pair2A.GetMinAngle();
				float Pair2MinAngleB = Pair2B.GetMinAngle();

				float ComparePair2 = (Pair2MinAngleA < Pair2MinAngleB) ? Pair2MinAngleA : Pair2MinAngleB; //take the smaller of the two

				//Pair 1 wins- dont need to delete closest, but do add Pair1B. and delete the losers
				if (ComparePair1 > ComparePair2) {
					std::cout << "Pair1 wins" << std::endl;
					Triangle* insertion = new Triangle(Pair1B);
					Triangulation->Insert(insertion);
				}
				else {
					std::cout << "Pair2 wins" << std::endl;
					Triangle* insertion = new Triangle(Pair2A);
					Triangulation->Insert(insertion);
					insertion = new Triangle(Pair2B);
					Triangulation->Insert(insertion);
					
					Triangulation->Delete(&closest);				
				}
				//if the tree WAS greater than just 1 triangle append to second closest as well
				//just an append so only comparing 2 triangles
			/*	if (starttreesize > 1) {
					Triangle Pair1C(*newvert, secondclosest.GetClosest(newvert), secondclosest.GetMiddle(newvert));
					Triangle Pair1D(*newvert, secondclosest.GetClosest(newvert), secondclosest.GetFurthest(newvert));
					Pair1MinAngleA = Pair1C.GetMinAngle();
					Pair1MinAngleB = Pair1D.GetMinAngle();

					std::cout << "about to insert" << std::endl;
					if (Pair1MinAngleA > Pair1MinAngleB) {
						Triangle* insertion = new Triangle(Pair1C);
						Triangulation->Insert(insertion);
						std::cout << "Inserted in first" << std::endl;
					}
					else {
						Triangle* insertion = new Triangle(Pair1D);
						Triangulation->Insert(insertion);
					}
				}
			*/

			}
			//Violations were found- if there is a violation there will be at least 4 points in the list
			else {
				Vertex* contrl = NULL;

		//CASE 2: 1 Violation- 3 pnts in the list
				if (violationnum == 1) {
					std::cout << YELLOW << "1 violation: " << DEFAULT << std::endl;
					Vertex* A = NULL;
					Vertex* B = NULL;
					Vertex* C = NULL;

					A = PointsToFix->GetHead();
					B = PointsToFix->GetHead();
					C = PointsToFix->GetHead();
					
					Triangle* Pair1A = new Triangle(A, B, C); //we know this is an illegal triangle with the addition of new vert

					//we know the combination of ABC is an invalid triangle- 
					//hence only 1 other way to split the quadrilateral which is this way
					Triangle Pair2A(*newvert, Pair1A->GetClosest(newvert), Pair1A->GetFurthest(newvert));
					Triangle Pair2B(*newvert, Pair1A->GetMiddle(newvert), Pair1A->GetFurthest(newvert));							
					Triangle Pair2C(*newvert, Pair1A->GetMiddle(newvert), Pair1A->GetClosest(newvert));							
					
					delete Pair1A;

					Triangle* insertion = new Triangle(Pair2A);
					std::cout << *insertion << std::endl;
					Triangulation->Insert(insertion);
					insertion = new Triangle(Pair2B);
					std::cout << *insertion << std::endl;
					Triangulation->Insert(insertion);
					insertion = new Triangle(Pair2C);
					Triangulation->Insert(insertion);
				}
				//1 triangle removed 3 added- change of 2
		//CASE 3: 2 Violations
				//there are 4 vertices in the list
				else if (violationnum == 2) {
					std::cout << YELLOW << "2 violations case" << DEFAULT << std::endl;
					//1. get an arbitrary point from the list
					contrl = PointsToFix->GetHead(); //3 remain in the list
					//2. get the 2 closest points to control in the list
					Vertex* T1 = PointsToFix->GetClosestItem(contrl); //does not remove the vertex from the list
					Vertex* T2 = PointsToFix->GetSecondClosestItem(contrl); //does not remove the vertex from the list

					//compare the possible triangles formed by T1, T2, control, and newvert
					Triangle Pair1A(*newvert, *T1, *contrl);
					Triangle Pair1B(*newvert, *T2, *contrl);
										
					//the pair include T1, T2, control was an invalid triangle- so it must be the other way
					
					Triangle* insertion = new Triangle(Pair1A);
					Triangulation->Insert(insertion);
					insertion = new Triangle(Pair1B);
					Triangulation->Insert(insertion);

					//now delete T1 and T2 from the list
					PointsToFix->RemoveItem(T1);
					PointsToFix->RemoveItem(T2);
					delete T1;
					delete T2;
					delete contrl;

					//now 1 item in the list C.
					contrl = PointsToFix->GetHead();
					//now 0 items in the list
				
					//now get the 2 closest triangles to C;
					Triangle closest = GetClosestStart(contrl);
					
					//NOT A PERMANENT SOLUTION
					Triangle Add1(*contrl, closest.GetClosest(contrl), closest.GetMiddle(contrl));
					std::cout << MAGENTA << Add1 << std::endl << std::endl;
					Triangle Add2(*contrl, GetSecondClosestStart(contrl).GetClosest(contrl), GetSecondClosestStart(contrl).GetMiddle(contrl));
					std::cout << MAGENTA << Add2 << DEFAULT << std::endl;
					insertion = new Triangle(Add1);
					Triangulation->Insert(insertion);
					insertion = new Triangle(Add2);
					Triangulation->Insert(insertion);

					delete contrl;

					//2 triangles removed, 4 added
				}
		//CASE 4: 3 Violations

				//5 vertices + new vert -- 3*3 - 2*2. 3 triangles 9 possible vertices, 2 shared edges. 2*2. 9-4 = 5 +1new vert
				else if (violationnum == 3) {
					contrl = PointsToFix->GetHead();
					std::cout << std::endl;
					PointsToFix->AddNode(newvert);
					PointsToFix->PrintList();
					Vertex* T1 = PointsToFix->GetClosestItem(contrl);
					Vertex* T2 = PointsToFix->GetSecondClosestItem(contrl);
					Vertex* T3 = PointsToFix->GetThirdClosestItem(contrl);
					//FORUMALATION ERRORS ON IRREGULAR SHAPES

					//compare triangles made by T1, T2, T3, and contrl
					Triangle Pair1A(*contrl, *T1, *T2);
					Triangle Pair1B(*T3, Pair1A.GetClosest(T3), Pair1A.GetMiddle(T3));
					float Pair1Min = 0;
					float P1AAngle = Pair1A.GetMinAngle();
					float P1BAngle = Pair1B.GetMinAngle();
					Pair1Min = (P1AAngle > P1BAngle) ? P1AAngle : P1BAngle;
					//-----------------------------------------------------
					Triangle Pair2A(*contrl, *T3, *T1);
					Triangle Pair2B(*T2, *T3, *T1);
					
					float Pair2Min = 0;
					float P2AAngle = Pair2A.GetMinAngle();
					float P2BAngle = Pair2B.GetMinAngle();
					Pair2Min = (P2AAngle > P2BAngle) ? P2AAngle : P2BAngle;

					Triangle CarryPairA;
					Triangle CarryPairB;
					if (Pair1Min > Pair2Min) {
						Triangle* insertion = new Triangle(Pair1A);
						Triangulation->Insert(insertion);
						insertion = new Triangle(Pair1B);
						Triangulation->Insert(insertion);

						CarryPairA = Pair1A;
						CarryPairB = Pair1B;
					}
					else {
						Triangle* insertion = new Triangle(Pair2A);
						Triangulation->Insert(insertion);
						insertion = new Triangle(Pair2B);
						Triangulation->Insert(insertion);

						CarryPairA = Pair2A;
						CarryPairB = Pair2B;
					}

					//now remove T1, T2, T3 from the list
					PointsToFix->RemoveItem(T1);
					PointsToFix->RemoveItem(T2);
					PointsToFix->RemoveItem(T3);

					delete contrl;
					delete T1;
					delete T2;
					delete T3;
				//2 items in the list remain.
					PointsToFix->PrintList();
					contrl = PointsToFix->GetHead(); //Get Control
					//get contrl's nearest triangle from the 2 just entered into the triangulation
					Triangle close = *CarryPairA.GetCloserTriangle(&CarryPairA, &CarryPairB, contrl);

					//get the two nearest points of the triangle- that don't have d = 0
					T1 = close.GetClosest(contrl);
					T2 = close.GetMiddle(contrl);

					//and get the shortest point to cntrl remaining in the list as the 4th of this quadrilateral
					T3 = PointsToFix->GetClosestItem(contrl);
					
					//compare and redraw
					Triangle Pair1C(*contrl, *T1, *T2);
					Triangle Pair1D(*contrl, *T3, *T1);
					
					//no point in defining 2 new floats to do the same thing
					P1AAngle = Pair1C.GetMinAngle();
					P1BAngle = Pair1D.GetMinAngle();
					Pair1Min = (P1AAngle > P1BAngle) ? P1AAngle : P1BAngle;

					//create new triangles to compare angles
					Triangle Pair2C(*contrl, *T3, *T2);
					Triangle Pair2D(*T1, *T3, *T2);

					P2AAngle = Pair2A.GetMinAngle();
					P2BAngle = Pair2B.GetMinAngle();
					Pair2Min = (P2AAngle < P2BAngle) ? P2AAngle : P2BAngle;
					
					Triangle CarryPairC;
					Triangle CarryPairD;

					if (Pair1Min > Pair2Min) {
						Triangle* insertion = new Triangle(Pair1C);
						Triangulation->Insert(insertion);
						insertion = new Triangle(Pair1D);
						Triangulation->Insert(insertion);
						
						CarryPairC = Pair1C;
						CarryPairD = Pair1D;
					}
					else {
						Triangle* insertion = new Triangle(Pair2C);
						Triangulation->Insert(insertion);
						insertion = new Triangle(Pair2D);
						Triangulation->Insert(insertion);

						CarryPairC = Pair2C;
						CarryPairD = Pair2D;
					}
										
					delete contrl;
					delete T1;
					delete T2;
					
				//T3 is the last in the list
					//get the closer of the first 2
					close = *CarryPairA.GetCloserTriangle(&CarryPairA, &CarryPairB, T3);
					//get the closer of the second 2
					//Triangle close2 = *CarryPairA.GetCloserTriangle(&CarryPairC, &CarryPairD, contrl);

					//draw with close
					T1 = close.GetMiddle(T3); //4,0 in example
					bool valid = true;
					
					Triangle Pair1E(*T3, *newvert, *T1);
					
					if (CheckValidity(Triangulation->Root, &Pair1E, valid)) {
						//add to triangulation
						Triangle* insertion = new Triangle(Pair1E);
						Triangulation->Insert(insertion);
					}
					else {
						if (close == CarryPairA)
							close = CarryPairB;
						else
							close = CarryPairA;
						delete T1;
						
						T1 = close.GetFurthest(T3);
						std::cout << YELLOW << *T1 << DEFAULT << std::endl;

						Triangle Pair1F(*T3, *newvert, *T1);
																								
						Triangle* insertion = new Triangle(Pair1F);
						Triangulation->Insert(insertion);

						/*else {
							std::cout << "BOTH INVALID" << std::endl;
							T1 = close.GetFurthest(T3);
							Triangle Pair1G(*T3, *newvert, *T1);
							delete T1;
							T1 = close.GetFurthest(T3);
							Triangle Pair1H(*T3, *newvert, *T1);
							Triangle* insertion = new Triangle(Pair1G);
							Triangulation->Insert(insertion);
							insertion = new Triangle(Pair1F);
							Triangulation->Insert(insertion);
						}*/
					}
					delete T1; 
					delete T3;
					//now remove T3 from the list, T1 and T2 came from an existing triangle
					//delete contrl;
				}
			//CASE 5: 4 violations
				else {
				std::cout << "4 violations found neato." << std::endl;
				}	
			}
	

		}
			//clean up lists
			//PointsToFix->EmptyList();
			delete PointsToFix;
			PointsToFix = NULL;
	}
	else
		std::cout << "Cant Add Point. Need a triangulation to begin inserting vertices." << std::endl;
}

void DelaunayT::GetIllegals(TreeNode<Triangle>* temp, Vertex* newvert) {
	/*
	Find all illegal triangles
	*/
	if (temp != Triangulation->NIL) {		
		//ILLEGAL TRIANGLE FOUND:
		if (temp->key->Circumscriber->IsinCircle(newvert)) {
			
			std::cout << "Illegal tri found!" << std::endl;
			
			IllegalTriangles.push_back(*(temp->key)); //add the triangle to a list of illegal triangles. Creates a copy
			
			//if the point is not in the list then add it to the list.
			if (!PointsToFix->InList(temp->key->A))
				PointsToFix->AddNode(*(temp->key->A));
			if (!PointsToFix->InList(temp->key->B))
				PointsToFix->AddNode(*(temp->key->B));
			if (!PointsToFix->InList(temp->key->C))
				PointsToFix->AddNode(*(temp->key->C));
		}		
		GetIllegals(temp->LChild, newvert);
		GetIllegals(temp->RChild, newvert);
	}
}

//destroys the whole tree
void DelaunayT::DeleteTriangulation() {
	if (Triangulation)
		Triangulation->EmptyTree();
}

//testing if get node works in the tree
void DelaunayT::GetTriangle(const Triangle* obj) {
	TreeNode<Triangle>* temp = Triangulation->GetNode(obj);
	if (temp) {
		std::cout << *(temp->key) << std::endl;
	}
	else
		std::cout << "?Not FOund?" << std::endl;
}

//testing deletion from tree
void DelaunayT::DeleteTriangle(Triangle* tri) {
	Triangulation->Delete(tri);
}

Triangle DelaunayT::GetClosestStart(const Vertex* pnt) {
	/*Return the closest triangle given a point
	*/
	std::cout << *pnt << std::endl;
	Triangle closest;
	float distance;
	if (Triangulation) {
		TreeNode<Triangle>* temp = Triangulation->Root;
		if (temp != Triangulation->NIL) {
			distance = CalculateDistance(pnt->X, pnt->Y, temp->key->Circumscriber->Center->X, temp->key->Circumscriber->Center->Y);
			closest = *Triangulation->Root->key;
			GetClosestRecursive(temp, pnt, closest, distance);
		}
	}
	return closest;
}

void DelaunayT::GetClosestRecursive(TreeNode<Triangle>* loc, const Vertex* pnt, Triangle& closest, float& distance) {
	if (loc != Triangulation->NIL) {
		float tempdist = CalculateDistance(pnt->X, pnt->Y, loc->key->Circumscriber->Center->X, loc->key->Circumscriber->Center->Y);
		if (tempdist < distance && tempdist != 0) {
			distance = tempdist;
			closest = *loc->key;
		}
		GetClosestRecursive(loc->LChild, pnt, closest, distance);
		GetClosestRecursive(loc->RChild, pnt, closest, distance);

	}
}

Triangle DelaunayT::GetSecondClosestStart(const Vertex* pnt) {
	/*Return the closest triangle given a point
	*/
	Triangle* closest = NULL; //point to closest triangle
	Triangle secondclosest; //copy of the second closest triangle; currently just a default triangle
	float closestdistance;
	float secondclosestdistance = 10000000;
	if (Triangulation) {
		TreeNode<Triangle>* temp = Triangulation->Root;
		if (temp != Triangulation->NIL) {
			closestdistance = CalculateDistance(pnt->X, pnt->Y, temp->key->Circumscriber->Center->X, temp->key->Circumscriber->Center->Y);
			closest = Triangulation->Root->key;
			GetSecondClosestRecursive(temp, pnt, closest, secondclosest, closestdistance, secondclosestdistance);
		}
	}
	return secondclosest;
}

void DelaunayT::GetSecondClosestRecursive(TreeNode<Triangle>* loc, const Vertex* pnt, Triangle* closest, Triangle& secondclosest, float& closestdistance, float& secondclosestdistance) {
	if (loc != Triangulation->NIL) {
		//new second closest
		float tempdist = CalculateDistance(pnt->X, pnt->Y, loc->key->Circumscriber->Center->X, loc->key->Circumscriber->Center->Y);
		if (tempdist > closestdistance && tempdist < secondclosestdistance) {
			secondclosestdistance = tempdist;
			secondclosest = *(loc->key);
		}
		//new closest
		else if (tempdist < closestdistance) {
			secondclosest = *closest;
			closest = loc->key; //move pointer forward
			secondclosestdistance = closestdistance; //move distances forward
			closestdistance = tempdist; //move closest distance to new closest distance
		}
		GetSecondClosestRecursive(loc->LChild, pnt, closest, secondclosest, closestdistance, secondclosestdistance);
		GetSecondClosestRecursive(loc->RChild, pnt, closest, secondclosest, closestdistance, secondclosestdistance);
	}
}

bool DelaunayT::CheckValidity(TreeNode<Triangle>* loc, Triangle* tri, bool& condition) {
	if (loc != Triangulation->NIL && condition) {
		if (loc->key->InCircumscriber(tri))
			condition = false;
		else {
			CheckValidity(loc->LChild, tri, condition);
			CheckValidity(loc->RChild, tri, condition);
		}
	}
	return condition;
}

bool DelaunayT::FindPointStart(const Vertex* trgt) {
	bool found = false;
	if (Triangulation) {
		if (Triangulation->Root != Triangulation->NIL) {
			if (*Triangulation->Root->key->A == *trgt || *Triangulation->Root->key->B == *trgt || *Triangulation->Root->key->C == *trgt) {
				found = true;
			}
			else {
				FindPointRecursive(Triangulation->Root->LChild, trgt, found);
				if(!found)
					FindPointRecursive(Triangulation->Root->RChild, trgt, found);
			}
		}
	}
	return found;
}

void DelaunayT::FindPointRecursive(TreeNode<Triangle>* loc, const Vertex* trgt, bool& cond) {
	if (loc != Triangulation->NIL) {
		if (*loc->key->A == *trgt || *loc->key->B == *trgt || *loc->key->C == *trgt) {
			cond = true;
		}
		else {
			FindPointRecursive(loc->LChild, trgt, cond);
			if(!cond)
			FindPointRecursive(loc->RChild, trgt, cond);
		}
	}
}

void DelaunayT::Print() {
	int size = (Triangulation->Nodenum) * 3;
	Vertex arrayofvert[size];
	int i = 0;
	Triangulation->ConverttoArray(Triangulation->Root, arrayofvert, i);
	
	std::cout << "Vertices in the Triangulation: " << std::endl;
	BubbleSort(arrayofvert, i);
	for (int j = 0; j < i; j++)
		std::cout << arrayofvert[j] << std::endl;

	std::cout << YELLOW << "Not drawn to scale" << DEFAULT << std::endl;
	std::cout << YELLOW << "For the imaginative type, envision lines." << DEFAULT << std::endl;
	float Xpercent = 0;
	int Xspace = 0;
	for (int j = 1; j < i; j++) {
		Xpercent = arrayofvert[j - 1].X - minX;
		Xpercent = (Xpercent / (maxX - minX));
		Xpercent *= 100;
		Xspace = (Xpercent / 10) * 1.5;
		//2 y shifts
		if (arrayofvert[j - 1].Y > arrayofvert[j].Y + 3) {
			for (int k = 0; k < Xspace; k++)
				std::cout << " ";
			std::cout << CYAN << FullBOX << DEFAULT << std::endl << std::endl;
		}
		//no y shift
		else if (arrayofvert[j - 1].Y == arrayofvert[j].Y) {
			for (int k = 0; k < Xspace; k++)
				std::cout << " ";
			std::cout << CYAN << FullBOX << DEFAULT;
		}
		else {
			for (int k = 0; k < Xspace; k++)
				std::cout << " ";
			std::cout << CYAN << FullBOX << DEFAULT << std::endl;
		}
	}
	std::cout << std::endl;
}

//sort data by y values
void DelaunayT::BubbleSort(Vertex* array, int size)
{
	int i, j;
	for (i = 0; i < size; i++)
	{
		for (j = 0; j < size - i - 1; j++)
		{
			if (array[j].Y < array[j + 1].Y) {
				Vertex temp;

				temp.X = array[j].X;
				temp.Y = array[j].Y;

				array[j].X = array[j + 1].X;
				array[j].Y = array[j + 1].Y;
				
				array[j+1].X = temp.X;
				array[j+1].Y = temp.Y;

			}
			else continue;
		}
	}
}