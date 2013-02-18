
local count = nil;
local sides = nil;
local mod_type = nil;
local mod_count = nil;
local ret = 0;

if table.getn( arg ) < 1 then
	io.write( "You must give a dice string as a parameter!\n" );
else
	if string.find( arg[ 1 ], "%d*[dD](%d+)[%p%d+]*" ) == nil then
		io.write( "Bad dice string!\n" );
	else
		count, sides, mod_type, mod_count = string.match( arg[ 1 ], "(%d+)[dD](%d+)[(%p)(%d+)]*" );
		if count == nil then count = 1 end
		ret = 0;
		io.write( "count: " .. count .. "\n" );
		io.write( "sides: " .. sides .. "\n" );
		for i = 1, count do
			math.randomseed( os.time() );
			ret = ret + math.random( 1, sides );
		end
		if mod_type ~= nil then
			if mod_type == "+" then
				ret = ret + mod_count
			elseif mod_type == "-" then
				ret = ret - mod_count
			else
				io.write( "Unregocnized modifier type: " .. mod_type .. "\n" );
			end
		end
	end
end

io.write( "count: " .. count .. "\n" );
io.write( "sides: " .. sides .. "\n" );
if mod_type ~= nil then
	io.write( "mod_type: " .. mod_type .. "\n" );
	io.write( "mod_count: " .. mod_count .. "\n" );
end
io.write( "ret: " .. ret .. "\n" );
