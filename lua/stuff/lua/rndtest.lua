-- Set the seed to random number generator
math.randomseed( os.time() );

local usage = "Usage: rndtest.lua [m [,n [,c]]]\n";
local argc = table.getn( arg );

local m = nil;
local n = nil;
local c = nil;
local i = 0;

if argc == 1 then
	m = tonumber( arg[ 1 ] );
	c = 1;
	if m == nil then
		io.write( usage );
		io.write( "Argument must be a number!\n" );
		os.exit( 1 );
	end
elseif argc == 2 then
	m = tonumber( arg[ 1 ] );
	n = tonumber( arg[ 2 ] );
	c = 1;
	if m == nil or n == nil then
		io.write( usage );
		io.write( "Arguments must be a number!\n" );
		os.exit( 1 );
	end
	c = 1;
elseif argc >= 3 then
	m = tonumber( arg[ 1 ] );
	n = tonumber( arg[ 2 ] );
	c = tonumber( arg[ 3 ] );
	if m == nil or n == nil or c == nil then
		io.write( usage );
		io.write( "Arguments must be a number!\n" );
		os.exit( 1 );
	end
else
	c = 1;
end
	

for i = 1, c do
	if argc == 0 then
		io.write( "Random number with range range [0,1): " .. math.random() .. "\n" );
	elseif argc == 1 then
		io.write( "Random number with range range [1, " .. m .. "]: " .. math.random( m ) .. "\n" );
	elseif argc >= 2 then
		io.write( "Random number with range range [" .. m .. ", " ..n .. "]: " .. math.random( m, n ) .. "\n" );
	end
end