function func()
	io.write( "Hello, World!\n" );
end

t = {};

if t.greeter == nil then
	io.write( "Unable to greet!!\n" );
end

t["greeter"] = func;

if t.greeter ~= nil and type( t.greeter ) == "function" then
	t.greeter();
end
