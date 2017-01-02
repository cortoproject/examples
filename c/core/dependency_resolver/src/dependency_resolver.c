#include "dependency_resolver.h"

#include "depresolver2.h"

int dependency_resolverMain(int argc, char *argv[]) {

    corto_stage s = corto_stageCreate();

    // Staging objects in random order
    corto_stage_add(s, "/p", "/Point", "text/corto", "x=0 y=0 next=/q", 0); // depends on Point, q
    corto_stage_add(s, "/p", "/Point", "text/corto", "x=10 y=20", 0); // depends on Point
    corto_stage_add(s, "/p", "/Point", "text/corto", "x=20 y=30 next=/q", 0); // depends on Point, q
    corto_stage_add(s, "/q", "/Point3D", "text/corto", "x=10 y=20 z=30", 0); // depends on Point3D
    corto_stage_add(s, "/Point3D/z", "member", "text/corto", "type=int32", 0); // depends on Point3D
    corto_stage_add(s, "/Point/x", "member", "text/corto", "type=int32", 0); // depends on Point
    corto_stage_add(s, "/Point/y", "member", "text/corto", "type=int32", 0); // depends on Point
    corto_stage_add(s, "/Point", "class", "text/corto", NULL, 3); // at least 3 objects in scope
    corto_stage_add(s, "/Point/next", "member", "text/corto", "type=/Point", 0); // depends on Point (circular)
    corto_stage_add(s, "/Point3D", "class", "text/corto", "base=/Point", 1); // depends on Point, at least 1 object in scope

    // Dependency ordered output sequence
    corto_object Point = corto_declareChild(root_o, "Point", corto_class_o);

    corto_object Point_x = corto_declareChild(Point, "x", corto_member_o);
    corto_fromstr(Point_x, "text/corto", "type=int32");
    corto_define(Point_x);

    corto_object Point_y = corto_declareChild(Point, "y", corto_member_o);
    corto_fromstr(Point_y, "text/corto", "type=int32");
    corto_define(Point_y);

    corto_object Point_next = corto_declareChild(Point, "next", corto_member_o);
    corto_fromstr(Point_next, "text/corto", "type=/Point");
    corto_define(Point_next);

    corto_define(Point);

    // discard older values for "p" because a newer value can be inserted
    corto_object p = corto_declareChild(root_o, "p", Point);
    corto_fromstr(p, "text/corto", "x=10 y=20");
    corto_define(p);

    corto_object Point3D = corto_declareChild(root_o, "Point3D", corto_class_o);
    corto_fromstr(Point3D, "text/corto", "base=/Point");

    corto_object Point3D_z = corto_declareChild(Point3D, "z", corto_member_o);
    corto_fromstr(Point3D_z, "text/corto", "type=int32");
    corto_define(Point3D_z);

    corto_define(Point3D);

    corto_object q = corto_declareChild(root_o, "q", Point3D);
    corto_fromstr(q, "text/corto", "x=10 y=20 z=30");
    corto_define(q);

    corto_updateBegin(p);
    corto_fromstr(p, "text/corto", "x=20 y=30 next=q");
    corto_updateEnd(p);






    return 0;
}
