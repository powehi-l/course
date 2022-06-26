from cyaron import *
for p in range(1,21):
    io = IO(str(p) + ".in","sample.out")
    v = 1000*p
    e = int(v * pow(pow(0.02*(v-1)/2,1/19),p - 1))
    g = Graph.UDAG(v,e,directed = False,weight_limit = (5,300),self_loop = False,repeated_edges = False)
    io.input_writeln('p','sp',v,e)
    print( p )
    for edge in g.iterate_edges():
        io.input_writeln('a',edge.start,edge.end,edge.weight)
