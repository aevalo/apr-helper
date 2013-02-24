Gem::Specification.new do |s|
  s.name               = "hola"
  s.version            = "0.0.1"
  s.default_executable = "hola"

  s.authors = ["Nick Quaranto"]
  s.date = %q{2010-04-03}
  s.description = %q{A simple hello world gem}
  s.email = %q{nick@quaran.to}
  s.homepage = %q{http://rubygems.org/gems/hola}
  s.require_paths = ["lib"]
  s.rubygems_version = %q{1.6.2}
  s.summary = %q{Hola!}
  s.test_files = ["test/test_hola.rb"]

  s.files = Dir.glob('lib/**/*.rb') +
            Dir.glob('ext/**/*{.c,.h}')
  s.extensions = ['ext/hola/extconf.rb']
  s.executables = ['hola']
end

