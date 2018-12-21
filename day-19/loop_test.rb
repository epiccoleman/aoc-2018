r4 = 1
r5 = 1
r2 = 60
r0 = 0

while ( r4 <= r2 ) do
  while (r5 <= r2) do
    r0 += r4 if (r5 * r4 == r2)
    r5 += 1
  end
  r4 += 1
  r5 = 1
end

puts r0
