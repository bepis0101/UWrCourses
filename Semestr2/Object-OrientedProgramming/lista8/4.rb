# Borys Adamiak
# Programowanie obiektowe Ruby
# Zad 4
# ruby 4.rb

class Jawna
    def initialize(word)
        @word = word
    end
    
    def to_s
        return @word
    end

    def zaszyfruj(key)
        word = ""
        @word.split('').each() { |c|
            word += 
            if key[c] == nil
                c
            else
                key[c]
            end
        }
        return Zaszyfrowana.new(word)
    end
end


class Zaszyfrowana
    def initialize(word)
        @word = word
    end
    
    def to_s
        return @word
    end
    
    def odszyfruj(key)
        word = ""
        key = key.invert()
        @word.split('').each { |c|
            word += 
                if key[c] == nil
                    c
                else
                    key[c]
                end
        }
        return Jawna.new(word)
    end
end


key = {
    'a' => 'b',
    'b' => 'c',
    'c' => 'd',
    'd' => 'e'
}
word = Jawna.new("abba")
cyphered = word.zaszyfruj(key)
print word, "->"
print cyphered, "->"
print cyphered.odszyfruj(key), "\n"