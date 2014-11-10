//
//  main.cpp
//  vmc_spin_ice
//
//  Created by Zhihao Hao on 2014-08-21.
//  Copyright (c) 2014 Zhihao Hao. All rights reserved.
//

#include <iostream>
#include <vector>
#include "MersenneTwister.h"
#include "routines.h"


int main()
{

    // insert code here...
    // system size L*L*L*4*4
    int L=1;
    int nh;
    int ntetra;
    //density
    double rho;
    double seedin=20.0;
    //spin configuration and
    MTRand *myrand=new MTRand();
    myrand->seed(seedin);
    seedin=myrand->rand();
    int *config;
    double *alpha;
    config=new int[L*L*L*4*4];
    //initialization!!!!!!!!!!!!!!!!!!!! TEST
    initialize(config,L,seedin);
    nh=16*(int)pow(L,3);
    ntetra=8*(int)pow(L,3);
    int ivic[nh][6];  // each site its 6 neighbours
    int tetra[ntetra][4]; // each tetrahedron and their 4 sites
    int connect[nh][2]; // each site connects two tetrahedra
    //construction of tables.
    latt(ivic,tetra,connect,L,nh,ntetra);
    int pos;
    int c1,c2,f1,f2,t;
    //Let's try the single spin update.
    int x,y,z,pyro,site,temp,count,total=100;
    int zpro=16*pow(L,2);
    int ypro=16*L;
    int xpro=16;
    for(z=0;z<L;z++)
    {
        for(y=0;y<L;y++)
        {
            for(x=0;x<L;x++)
            {
                for(pyro=0;pyro<4;pyro++)
                {
                    for(site=0;site<4;site++)
                    {
                        std::cout<<config[z*zpro+y*ypro+x*xpro+pyro*4+site]<<'\n';
                    }
                }
            }
        }
    }
    pos=0;
    t=connect[pos][0];
    c1=qcharge(t,tetra);
    f1=c1-2*config[pos];
    t=connect[pos][1];
    c2=qcharge(t,tetra);
    f2=c2+2*config[pos];
    //charge(config,L,pos,c1,c2,f1,f2);
    //we are trying to figure out the charge of the particular tetrahedron
    //Test!!!!!!!!
    //update.
    int flag=0;
    double prob,density,densitysquare,tempature;
    pos=15;
    prob=0.2;
    density=0.3;
    densitysquare=pow(density,2.0);
    std::cout<<config[pos]<<"\n";
    //singlespin_update_new(config,L,pos,prob,densitysquare,flag);
    std::cout<<config[pos]<<"\n";
    //test the sweep
    flag=1;
    tempature=0.3;
    for(count=0;count<total;count++)
    {
        seedin=myrand->rand();
    //singlespin_sweep(config,L,tempature,flag,seedin);
    }
    for(z=0;z<L;z++)
    {
        for(y=0;y<L;y++)
        {
            for(x=0;x<L;x++)
            {
                for(pyro=0;pyro<4;pyro++)
                {
                    for(site=0;site<4;site++)
                    {
                        std::cout<<config[z*zpro+y*ypro+x*xpro+pyro*4+site]<<'\n';
                    }
                }
            }
        }
    }
    return 0;
}

