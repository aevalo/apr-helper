require( "testpackage.greet" );

io.write( "Script name: " .. arg[ 0 ] .. "\n" );

if table.getn( arg ) < 1 then
  io.write( "No arguments!\n" );
else
  for argi = 1, table.maxn( arg ) do
    io.write( arg[ argi ] .. "\n" );
  end
end

greet.greet();

os.exit();
