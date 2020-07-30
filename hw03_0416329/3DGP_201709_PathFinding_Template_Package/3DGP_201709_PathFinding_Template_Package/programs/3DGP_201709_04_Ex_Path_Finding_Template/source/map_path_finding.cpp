#include "map.h"
using namespace std;

void MAP::setInvisibleAllPathPoints( )
{
    for ( int j = 0; j < mMaxNumOfPathPoints; ++j ) {
        mSceneNodes_Path[j]->setVisible( false );
    }
}

//
// Compute the grid cell indices (ix, iz) for input point p.
// The grid is defined on the x-z plane.
//
void MAP::computeIndices( const Vector3 &p, int &iz, int &ix ) const
{
    Vector3 relative_p = p - mMinSpace;
    ix = (relative_p.x + mDWidth.x*0.5 )/ mDWidth.x ;
    iz = (relative_p.z + mDWidth.z*0.5 ) / mDWidth.z;
    if ( ix < 0 ) ix = 0;
    if ( ix >= mNX - 1 ) ix = mNX - 1;

    if ( iz < 0 ) iz = 0;
    if ( iz >= mNZ - 1 ) iz = mNZ - 1;
}

Vector3 MAP::computePointPosition( int iz, int ix ) const
{
    Real x, z;
    x = ix*mDWidth.x + mMinSpace.x;
    z = iz*mDWidth.z + mMinSpace.z;
    return Vector3( x, 0.0, z );

}

void MAP::setPathPoint( int index, int ix, int iz,SceneManager* mSceneMgr )
{
    Vector3 p = computePointPosition( ix, iz);
	SceneNode *temp;
	temp = mSceneMgr->getRootSceneNode()->createChildSceneNode();
    temp->setPosition( p );
    temp->setVisible( true );
	mSceneNodes_Path.push_back(temp);

}

void MAP::showPath(SceneManager* mSceneMgr,int index)
{
	string name;
	genNameUsingIndex("sp", index, name);
	//cout<<"111"<<endl;
	mSceneMgr->destroyEntity(name);
	Entity *ent = mSceneMgr->createEntity( name, "sphere.mesh" ); 
	//cout<<"222"<<endl;
	ent->setMaterialName("Examples/SphereMappedRustySteel");
	//cout<<"333"<<endl;
	mSceneNodes_Path[index]->attachObject(ent);
	mSceneNodes_Path[index]->scale(0.1,0.1,0.1);
	//cout<<"444"<<endl;
}

void MAP::setPathPoint( int index, const Vector3 &position )
{
    mSceneNodes_Path[index]->setPosition( position );
    mSceneNodes_Path[index]->setVisible( true );
}

//
// S <- A <- B <- G
// Use pre-traversal to get: G, B, A, S
//
// Traverse the linked list using the parent pointer.
//
//  if ( node == 0 ) return;
//  constructPathPoints( node->parent );
//  mPathPoints.push_back( node->position );
//
void MAP::constructPathPoints( MapNode *node )
{
	//cout<<"cons2"<<endl;
    if ( node == 0 ) return;
	//cout<<"const2x"<<node->ix<<"z"<<node->iz<<endl;
    constructPathPoints( node->parent );
	//cout<<"cons3"<<endl;
	node->position = computePointPosition(node->ix,node->iz);
    mPathPoints.push_back( node->position );
}


void MAP::constructPathPoints( int goal_ix, int goal_iz )
{
    mPathPoints.clear( );
    MapNode *goalNode = &mMapNodes[goal_ix][goal_iz];
	//cout<<"x"<<goal_ix<<"z"<<goal_iz<<endl;
    constructPathPoints( goalNode );
    
}


std::vector<Vector3> MAP::getPathPoints( ) const
{
    return mPathPoints;
}

//
// Implement the A* algorithm
//
void MAP::performAStarPathFinding( ) 
{
    //cout << "here" << endl;
    mOpenList.clear( );
    mClosedList.clear( );
    double g, h;
    g = 0.0;
    //h = getCostBetweenTwoNodes( mStartNode, mGoalNode );
	mStartNode->g=0;
	addNodeToOpenList(mStartNode);
	int test=0;
	//cout<<"before while"<<endl;
	//cout<<"openlist size"<<mOpenList.empty()<<endl;
	while(!mOpenList.empty())
	{
		//cout<<"test"<<test<<endl;
		MapNode* n = mOpenList.front();
		if(n==mGoalNode)
		{
			return;
		}
		mClosedList.push_back(n);
		//mOpenList.erase(mOpenList.begin());
		MapNode *f = mOpenList.front();
		//cout<<"shix"<<f->ix<<"z"<<f->iz<<endl;
		mOpenList.erase(mOpenList.begin());
		for(int i=0;i<4;i++)
		{
			//cout<<"test"<<i<<endl;

			//here I calculate the neighbors

			MapNode *n1;
			switch(i){
				case 0: if(n->ix!=0){if(mMapNodes[n->ix-1][n->iz].flgCanMove==false)continue;else n1=&mMapNodes[n->ix-1][n->iz];}break;
				case 1: if(n->ix!=19){if(mMapNodes[n->ix+1][n->iz].flgCanMove==false)continue;else n1=&mMapNodes[n->ix+1][n->iz];}break;
				case 2: if(n->iz!=0){if(mMapNodes[n->ix][n->iz-1].flgCanMove==false)continue;else n1=&mMapNodes[n->ix][n->iz-1];}break;
				case 3: if(n->iz!=19){if(mMapNodes[n->ix][n->iz+1].flgCanMove==false)continue;else n1=&mMapNodes[n->ix][n->iz+1];}break;
			}
			//cout<<"x"<<n1->ix<<"y"<<n1->iz<<endl;

			//here i calculate the costs

			int g,h,f;
			g = n->g + 1;
			h = abs(n1->ix-mGoalNode->ix)+abs(n1->iz-mGoalNode->iz);
			//cout<<"nz"<<n1->iz<<"nx"<<n1->ix<<"mGz"<<mGoalNode->iz<<"mGx"<<mGoalNode->ix<<endl;
			f = g+h;
			//cout<<"h"<<h<<endl;
			int ind,ind2,op=0,cl=0;
			//cout<<"3sizeo"<<mOpenList.size()<<endl;
			int flg =0;

			//in here if the the neighbor is in the open list and the new path is not better we skip

			for(int k=0;k<mOpenList.size();k++)
			{
				if(mOpenList[k]==n1)
				{
					//cout<<"works1"<<endl;
					if(n1->f!=-1 && f>=n1->f)flg=1;else {ind = k;op=1;}
				}
			} if(flg==1)continue;

			//if neighbor is on closed we skip

			for(int k=0;k<mClosedList.size();k++)
			{
				if(mClosedList[k]==n1)
				{
					//cout<<"works2"<<endl;
					//if(n1->f!=-1 && f>=n1->f)flg=1;else {ind2=k;cl=1;}
					flg=1;
				}
			}if(flg==1)continue;
			//cout<<"4sizeo"<<mOpenList.size()<<endl;
			if(op==1) mOpenList.erase(mOpenList.begin()+ind);
			if(cl==1) mClosedList.erase(mClosedList.begin()+ind2);
			//cout<<"5sizeo"<<mOpenList.size()<<endl;

			//we set costs and parent

			n1->parent=n;
			n1->f=f;
			n1->g=g;
			n1->h=h;
			addNodeToOpenList(n1);
			

		}
	}
	//cout<<"didnt find path"<<endl;
}

bool MAP::performPathFinding( const Vector3 &p, const Vector3 &q, SceneManager* mSceneMgr )
{
	int x,y;
	//cout<<"1"<<endl;
	computeIndices(q,x,y);
	mGoalNode = &mMapNodes[x][y];
	computeIndices(p,x,y);
	mStartNode = &mMapNodes[x][y];
	mGoalNode->position = q;
	mStartNode->position=p;
	//cout<<"3"<<endl;
	computeIndices(p,mStartNode->ix,mStartNode->iz);
	//cout<<"4"<<endl;
	clearAllCosts(mSceneMgr );
	if(mGoalNode->flgCanMove==0) return 0;
	performAStarPathFinding( );
	//cout<<"5"<<endl;
	constructPathPoints(mGoalNode->ix,mGoalNode->iz);
	//cout<<"6"<<endl;
	//cout<<mPathPoints.size()<<endl;
	for(int i=0;i<mPathPoints.size();i++)
	{
		int x,z;
		computeIndices(mPathPoints[i],x,z);
		//cout<<"11"<<endl;
		setPathPoint(i,x,z,mSceneMgr);
		//cout<<"22"<<endl;
		showPath(mSceneMgr,i);
		//cout<<"33"<<endl;
	}
	//cout<<"7"<<endl;
	return 1;
}

void MAP::clearAllCosts(SceneManager* mSceneMgr )
{
	for(int i=0;i<mNZ;i++)
	{
		for(int j=0;j<mNX;j++)
		{
			mMapNodes[i][j].f=-1;
			mMapNodes[i][j].g=-1;
			mMapNodes[i][j].h=-1;
			mMapNodes[i][j].parent=0;
		}
	}
	for(int i=mSceneNodes_Path.size()-1; i>=0;i--)
	{
		string name;
		genNameUsingIndex("sp", i, name);
		mSceneMgr->destroyEntity(name);
		mSceneNodes_Path[i]->removeAndDestroyAllChildren();
		mSceneNodes_Path.erase(mSceneNodes_Path.begin()+i);
	}

}
//double getCostBetweenTwoNodes( const MapNode *p0, const MapNode *p1 ) const; 
//MapNode *getNodeFromOpenList( );
//void computeNeighbor( MapNode *node, std::vector<MapNode *> &neightbors);
//void removeNodeFromOpenList( MapNode *node );
//void removeNodeFromClosedList( MapNode *node );
void MAP::addNodeToOpenList( MapNode *node )
{
	//cout<<"sizeof"<<mOpenList.size()<<endl;
	for(int i=0;i<mOpenList.size();i++)
	{
		//cout<<"add1"<<endl;
		if(node->f<mOpenList[i]->f)
		{
			mOpenList.insert(mOpenList.begin()+i,node);
			return;
		}
	}
		//cout<<"Added to openlist"<<endl;
		mOpenList.push_back(node);
		//cout<<"2sizeof"<<mOpenList.size()<<endl;
		return;
	
}
//void setPathPoint( int index, const Vector3 &position );