## Borys Adamiak
## Programowanie Obiektowe lista 9
## Zadania 1 i 3
## ruby Function.rb 

class Function
    
    def initialize(&block)
        @function = block
    end

    def value(x)
        @function.call(x)
    end

    def zero(a, b, epsilon)
        x1 = a
        x2 = b
        while (x1-x2).abs > epsilon
            mid = (x1+x2) / 2.0
            if value(mid).abs < epsilon
                return mid
            elsif value(mid) * value(x1) < 0.0
                x2 = mid
            else
                x1 = mid
            end
        end
        nil
    end
    def field(a, b)
        n = 100000
        dx = (b-a) * 1.0 / n
        sum = 0.0
        (0..n).each do |i|
            y1 = value(a + i*dx)
            y2 = value(a + (i+1)*dx)
            sum += ((y1+y2)/2)*dx
        end
        sum
    end
    def deriv(x)
        h = 0.0001
        # lim h->0
        (value(x+h) - value(x)) / h
    end
    def plot(minx, maxx, miny, maxy, precision = 0.5)
        (miny..maxy).reverse_each do |y|  
            print " "
          
            (minx..maxx).each do |x|
            begin
                if (value(x) - y).abs < precision
                print "@"
                elsif x == 0 and y == 0
                    print "+"
                elsif x == 0
                    print "|"
                elsif y == 0
                    print "-"
                else
                    print " "
                end
            rescue Exception
                if x == 0 and y == 0
                    print "+"
                elsif x == 0
                    print "|"
                elsif y == 0
                    print "-"
                else
                    print " "
                end
                end
             end
          puts " "
            end
      end
end

blok = proc { |x| x*x }

x = Function.new(&blok)
puts x.value(10)
puts x.zero(-1, 1, 0.1)
puts x.field(0, 1)
puts x.deriv(5)
x.plot(-5, 5, -5, 5)
x = Function.new {|x| Math.cos(x)}
puts x.deriv(0)
puts x.zero(0, 2*Math::PI, 0.001)
x.plot(-10, 10, -2, 2)