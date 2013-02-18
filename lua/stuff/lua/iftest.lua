function func1()
	io.write( "func1() returns false...\n" );
	return false;
end

function func2()
	io.write( "func2() returns true...\n" );
	return true;
end

io.write( "Evaluating \"func1() and func2()\"...\n" );
if func1() and func2() then
	io.write( "Short-circuit evaluation test #1\n" );
end
io.write( "Evaluating \"not func1() and func2()\"...\n" );
if not func1() and func2() then
	io.write( "Short-circuit evaluation test #2\n" );
end
