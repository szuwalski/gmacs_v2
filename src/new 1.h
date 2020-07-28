
  for ( i = syr; i <= nyrRetro; i++ )
   for ( int j = 1; j <= nseason; j++ )
    {
     for ( ig = 1; ig <= n_grp; ig++ )
      {
       h = isex(ig);
       isizeTrans = iYrIncChanges(h,i);
       m = imature(ig);
       o = ishell(ig);

       x = d4_N(ig)(i)(j);
       // Mortality (natural and fishing)
       x = x * S(h,m)(i)(j);
       if ( nshell == 1 )
        {
		if(nmature == 1)
		 {
		 // Molting and growth
         if (j == season_growth)
           {
            y = elem_prod(x, 1.0 - molt_probability(h)(i)); // did not molt, 
            x = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, 
            x = x + y;
           }
         // Recruitment
         if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
         if (j == nseason) d4_N(ig)(i+1)(1) = x;  else  d4_N(ig)(i)(j+1) = x;
		 }
        if(nmature == 2)
		 {
		  if ( m == 1 ) // mature
          {
           //No molting, growth, or recruitment for mature animals
           if (j == nseason) d4_N(ig)(i+1)(1) = x; else  d4_N(ig)(i)(j+1) = x;
          }
          if ( m == 2 ) // immature
          {
          // Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             //z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); 		// molted to maturity
             //x = elem_prod(x, 1 - molt_probability(h)(i)) * growth_transition(h,isizeTrans);    // molted, but immature
			 z = elem_prod(x * growth_transition(h,isizeTrans), molt_probability(h)(i)) ; 		// molted to maturity
             x = elem_prod(x * growth_transition(h,isizeTrans), 1 - molt_probability(h)(i)) ;    // molted, but immature
            }
		   if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
           if (j == nseason)
            { d4_N(ig-1)(i+1)(1) += z; d4_N(ig)(i+1)(1) = x; }
            else
            { d4_N(ig-1)(i)(j+1) += z; d4_N(ig)(i)(j+1) = x; }
          }	 
		 }
        }
       else
        {
         if ( o == 1 ) // newshell
          {
          // Molting and growth
           if (j == season_growth)
            {
             y = elem_prod(x, 1.0 - molt_probability(h)(i)); // did not molt, become oldshell
             x = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, stay newshell
            }
           //Recruitment
           if (j == season_recruitment) x += recruits(h)(i) * rec_sdd(h);
           if (j == nseason) d4_N(ig)(i+1)(1) = x; else  d4_N(ig)(i)(j+1) = x;
          }
         if ( o == 2 ) // oldshell
          {
          //Molting and growth
           z.initialize();
           if (j == season_growth)
            {
             z = elem_prod(x, molt_probability(h)(i)) * growth_transition(h,isizeTrans); // molted and grew, become newshell
             x = elem_prod(x, 1 - molt_probability(h)(i)) + y; // did not molt, remain oldshell and add the newshell that become oldshell
            }
           if (j == nseason)
            { d4_N(ig-1)(i+1)(1) += z; d4_N(ig)(i+1)(1) = x; }
            else
            { d4_N(ig-1)(i)(j+1) += z; d4_N(ig)(i)(j+1) = x; }
          }
        }

	} // ig
  } // i and j