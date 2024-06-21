#include <iostream>
#include <vector>

class Property {
public:
    int id;
    double latitude;
    double longitude;
    double price;
    int bedrooms;
    int bathrooms;

    Property(int id, double lat, double lon, double price, int beds, int baths)
        : id(id), latitude(lat), longitude(lon), price(price), bedrooms(beds), bathrooms(baths) {}
};

class QuadTreeNode {
public:
    double minLat, minLon, maxLat, maxLon;
    std::vector<Property*> properties;
    QuadTreeNode *nw, *ne, *sw, *se;
    static const int MAX_PROPERTIES = 4;

    QuadTreeNode(double minLat, double minLon, double maxLat, double maxLon)
        : minLat(minLat), minLon(minLon), maxLat(maxLat), maxLon(maxLon), nw(nullptr), ne(nullptr), sw(nullptr), se(nullptr) {}

    bool isLeaf() {
        return nw == nullptr && ne == nullptr && sw == nullptr && se == nullptr;
    }

    bool contains(Property* property) {
        return property->latitude >= minLat && property->latitude <= maxLat &&
               property->longitude >= minLon && property->longitude <= maxLon;
    }

    void subdivide() {
        double midLat = (minLat + maxLat) / 2;
        double midLon = (minLon + maxLon) / 2;
        nw = new QuadTreeNode(minLat, minLon, midLat, midLon);
        ne = new QuadTreeNode(minLat, midLon, midLat, maxLon);
        sw = new QuadTreeNode(midLat, minLon, maxLat, midLon);
        se = new QuadTreeNode(midLat, midLon, maxLat, maxLon);
    }
};

void insertQuadTree(QuadTreeNode* node, Property* property) {
    if (!node->contains(property)) return;

    if (node->isLeaf()) {
        node->properties.push_back(property);
        if (node->properties.size() > QuadTreeNode::MAX_PROPERTIES) {
            node->subdivide();
            for (auto& prop : node->properties) {
                insertQuadTree(node->nw, prop);
                insertQuadTree(node->ne, prop);
                insertQuadTree(node->sw, prop);
                insertQuadTree(node->se, prop);
            }
            node->properties.clear();
        }
    } else {
        insertQuadTree(node->nw, property);
        insertQuadTree(node->ne, property);
        insertQuadTree(node->sw, property);
        insertQuadTree(node->se, property);
    }
}
class BTreeNode {
public:
    std::vector<double> keys;
    std::vector<Property*> properties;
    std::vector<BTreeNode*> children;
    bool leaf;
    static const int T = 3;  // Minimum degree (defines the range for the number of keys) This maybe vary as required

    BTreeNode(bool leaf) : leaf(leaf) {}

    void insertNonFull(Property* property);
    void splitChild(int i, BTreeNode* y);
};

class BTree {
public:
    BTreeNode* root;

    BTree() {
        root = new BTreeNode(true);
    }

    void insert(Property* property) {
        BTreeNode* r = root;
        if (r->keys.size() == 2 * BTreeNode::T - 1) {
            BTreeNode* s = new BTreeNode(false);
            s->children.push_back(r);
            s->splitChild(0, r);
            int i = 0;
            if (s->keys[0] < property->price) i++;
            s->children[i]->insertNonFull(property);
            root = s;
        } else {
            r->insertNonFull(property);
        }
    }
};

void BTreeNode::insertNonFull(Property* property) {
    int i = keys.size() - 1;
    if (leaf) {
        keys.push_back(0);
        properties.push_back(nullptr);
        while (i >= 0 && keys[i] > property->price) {
            keys[i + 1] = keys[i];
            properties[i + 1] = properties[i];
            i--;
        }
        keys[i + 1] = property->price;
        properties[i + 1] = property;
    } else {
        while (i >= 0 && keys[i] > property->price) i--;
        if (children[i + 1]->keys.size() == 2 * T - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < property->price) i++;
        }
        children[i + 1]->insertNonFull(property);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->leaf);
    for (int j = 0; j < T - 1; j++) {
        z->keys.push_back(y->keys[j + T]);
        z->properties.push_back(y->properties[j + T]);
    }
    if (!y->leaf) {
        for (int j = 0; j < T; j++) {
            z->children.push_back(y->children[j + T]);
        }
    }
    y->keys.resize(T - 1);
    y->properties.resize(T - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[T - 1]);
}

int main() {
    // Creating root nodes for Quad-tree and B-tree
    QuadTreeNode* quadRoot = new QuadTreeNode(-90, -180, 90, 180);
    BTree bTree;


    Property p1(1, 37.7749, -122.4194, 1000000, 3, 2);
    Property p2(2, 34.0522, -118.2437, 800000, 2, 1);
    Property p3(3, 40.7128, -74.0060, 1500000, 4, 3);

    // Inserting properties into Quad-tree and B-tree
    insertQuadTree(quadRoot, &p1);
    insertQuadTree(quadRoot, &p2);
    insertQuadTree(quadRoot, &p3);
    bTree.insert(&p1);
    bTree.insert(&p2);
    bTree.insert(&p3);



    return 0;
}


