module( "greet", package.seeall );

function greet()
  io.write( "What is your name? " );
  local name = io.read();
  if string.len( name ) < 1 then
    name = "stanger";
  end
  io.write( "Hello, " .. name .. "!\n" );
end