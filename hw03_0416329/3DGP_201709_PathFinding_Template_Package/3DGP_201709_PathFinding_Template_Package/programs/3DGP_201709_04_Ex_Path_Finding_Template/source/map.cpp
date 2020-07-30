#include "map.h"

MAP::MAP( )
{
    mNX = 20;
    mNZ = 20;
    mMinSpace = Vector3( -250.0, 0.0, -250.0 );
    mMaxSpace = Vector3( 250.0, 0.0, 250.0 );
    mSceneNodes = 0;
    mEntitys = 0;
	for(int i=0;i<MAX_NX;i++)
	{
		for(int j=0;j<MAX_NZ;j++)
		{
			mMapNodes[i][j].ix=i;
			mMapNodes[i][j].iz=j;
		}
	}
    reset( );
}

void MAP::setDimension( int nx, int nz )
{
    mNX = nx;
    mNZ = nz;
    reset( );
}

void MAP::reset( )
{
    for ( int j = 0; j < MAX_NZ; ++j ) {
        for ( int i = 0; i < MAX_NX; ++i ) {
            mMapNodes[i][j].flgCanMove = false;
        }
    }
}

void MAP::generateMap( SceneManager* mSceneMgr )
{
    mSceneNodes = new SceneNode*[mNX*mNZ];
    mEntitys = new Entity*[mNX*mNZ];
    Vector3 w = mMaxSpace - mMinSpace;
    double dx = w.x/(mNX-1);
    double dz = w.z/(mNZ-1);
    //
    mDWidth = Vector3( dx, 0.0, dz );

    float size = 0.5;
    Vector3 scales = size*Vector3(0.35, 1.0, 0.35);
    float translate_y = -size*40;
    for ( int j = 0; j < mNZ; ++j ) {
        for ( int i = 0; i < mNX; ++i ) {
            int index = i + j*mNX;
            double x, y, z;
            y = 0.0;
            x = i*dx + mMinSpace.x;
            z = j*dz + mMinSpace.z;
            //
            mMapNodes[i][j].flgCanMove = false;
            mMapNodes[i][j].ix = i;
            mMapNodes[i][j].iz = j;

        mMapNodes[i][j].position = Vector3( x, 0.0, z );
            //
             mSceneNodes[ index ] = mSceneMgr->getRootSceneNode()->createChildSceneNode( );
            mSceneNodes[ index ]->setPosition( Vector3( x, y, z ) );
            mSceneNodes[ index ]->scale(scales.x, scales.y, scales.z );
            mSceneNodes[ index ]->translate( 0.0, translate_y, 0.0);
            String name;
		genNameUsingIndex("br", index, name);

            mEntitys[ index ] = mSceneMgr
			->createEntity( name, "cube.mesh" ); 
            mEntitys[ index ]->setMaterialName("Examples/SphereMappedRustySteel");
            mSceneNodes[ index ]->attachObject( mEntitys[ index ] );
			
        
        }

         
    }
    //
    
    for ( int j = 1; j < mNZ-1; ++j ) {
        for ( int i = 1; i < mNX-1; ++i ) {
            int index = i + j*mNX;
			if(!(i==0 || (j==2 && i!=1 && i!=18) || (j==4 && i==2) || (j==5 && i==2) || (j==7 && i!=1 && i!=18) || (j==14 && i!= 18) || (j==17 && i!=1) || i==19 || j==0 || j==19)){
            mSceneNodes[ index ]->setVisible( false );
            mMapNodes[j][i].flgCanMove = true;
			}
        }
    }
    

}