function deg2rad( x )
  -- x degrees = (2*PI * x radians)/360 = (PI * x radians)/180.
  return ( math.pi * x ) / 180;
end

function rad2deg( x )
  -- x radians = (360 * x degrees)/2*PI = (180 * x degrees)/PI.
  return ( 180 * x ) / math.pi;
end

io.write( "1 radian is " .. math.deg( 1 ) .. " degrees.\n" );
io.write( "1 radian is " .. rad2deg( 1 ) .. " degrees.\n" );

io.write( "360 degrees is " .. math.rad( 360 ) .. " radians.\n" );
io.write( "360 degrees is " .. deg2rad( 360 ) .. " radians.\n" );

io.write( "1 degrees is " .. deg2rad( 1 ) .. " radians.\n" );
