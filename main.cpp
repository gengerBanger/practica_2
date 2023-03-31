#include <iostream>
#include <vector>
using namespace std;
struct ListItem{
    int data;
    ListItem * head;
    ListItem * tail;
};

class List{
    private :

    ListItem * begin;

    short int len;

    void fillList_rand(){
        srand(time(nullptr));
        ListItem * curr = nullptr, * next = nullptr;
        for(int i = 0; i < len; i++){
            curr = new ListItem;
            curr->data =  rand() % 100;
            curr->tail = next;
            if(next) next->head = curr;
            next = curr;
        }
        curr->head = nullptr;
        begin = curr;
    }

    void fillList_hand(){
        ListItem * curr = nullptr, * next = nullptr;
        vector <int> buff;
        int * i = new int(0), p;
        do{
            cin >> p;

            buff.push_back(p);
            if(!cin){
                buff.pop_back();
                break;
            }
            *i = *i + 1;
        }
        while(cin);
        len = *i;
        delete i;

        for(int j = len - 1 ;j >= 0; j--){
            curr = new ListItem;
            curr->data = buff[j];
            curr->tail = next;
            if(next) next->head = curr;
            next = curr;
        }
        curr->head = nullptr;
        begin = curr;
    }
    public:

    explicit List(char key){
        switch (key) {
            case '1':
            {
                cout << "~~Enter amount of items~~\n";
                cin >> len;
                fillList_rand();
                outList(begin);
                break;
            }
            case '2':
            {
                cout << "~~Enter the items~~\n";
                fillList_hand();
                outList(begin);
                break;
            }
        }
    }
    ~List(){
        ListItem * next;
        while(begin){
            next = begin;
            delete next;
            begin = begin->tail;
        }
    }
    ListItem * GetBegin(){
        return begin;
    }

    int GetLen(){
        return len;
    }

    void outList(ListItem * beg){
        if (beg == nullptr) cout << "\t~~The list is empty~~\n";
        else{
            cout <<"---> ";
            while(beg){
                cout << beg->data<< " ";
                beg = beg->tail;
            }
        }
        cout << "\n\n";
    }
    ListItem * searchItemIndex(int index){
        ListItem * beg = begin;
        for(int i = 1; i <= len; i++){
            if(i == index) return beg;
            beg = beg->tail;
        }
        cout << "~~Element is not found~~\n";
        return nullptr;
    }

    int searchItemData(int data){
        ListItem * beg = begin;
        for(int i = 1; i <= len; i++){
            if(beg->data == data) return i;
            beg = beg->tail;
        }
        cout << "~~Element is not found~~\n";
        return 0;
    }

    void deleteItemIndex(int index){
        ListItem * item = searchItemIndex(index);
        if(index == 1 && len >= 2) begin = begin->tail;
        if(index == 1 && len == 1){
            len = 0;
            begin = nullptr;
            delete item;
        }
        else{
            if(item){
                if (item->head == nullptr){
                    item->tail->head = nullptr;
                    delete item;
                }
                else{
                    if(item->tail == nullptr){
                        item->head->tail = nullptr;
                        delete item;
                    }
                    else{
                        item->head->tail = item->tail;
                        item->tail->head = item->head;
                        delete item;
                    }
                }
                --len;
            }
        }
        outList(begin);
    }

    void deleteItemData(int data){
        int * buff = new int(searchItemData(data));
        if( *buff == 1) begin = begin->tail;
        ListItem * item = searchItemIndex(*buff);
        if(item){
            if (item->head == nullptr){
                item->tail->head = nullptr;
                delete item;
            }
            if(item->tail == nullptr){
                item->head->tail = nullptr;
                delete item;
            }
            else{
                item->head->tail = item->tail;
                item->tail->head = item->head;
                delete item;
            }
            len--;
        }
        outList(begin);
        delete buff;
    }

    void insertItem(int index, int dataIt){
        if(len == 0){
            ListItem * curr = new ListItem;
            begin = curr;
            curr->tail = nullptr;
            curr->head = nullptr;
            curr->data = dataIt;
        }
        else{
            ListItem * shiftable_item , * item = new ListItem;
            if (index == len + 1) {
                shiftable_item = searchItemIndex(len);
                shiftable_item->tail = item;
                item->head = shiftable_item;
                item->tail = nullptr;
                item->data = dataIt;
            }
            shiftable_item = searchItemIndex(index);
            if(shiftable_item) {
                    if (index == 1) begin = item;
                    else shiftable_item->head->tail = item;
                    item->head = shiftable_item->head;
                    item->tail = shiftable_item;
                    item->data = dataIt;
                    shiftable_item->head = item;
                }
        }
            outList(begin);
            len++;
    }

    void permutationItems(int item1, int item2){
        if(item1 > item2) swap(item1,item2);
        ListItem *p1(searchItemIndex(item1)), *p2(searchItemIndex(item2));
        if(p1 && p2){
            if(item1 == 1) begin = p2;
            ListItem ** buff = new ListItem *;
            if(p1->head == nullptr || p2->tail == nullptr){
                if(p2->tail != nullptr){
                    swap(p2->tail->head,p1->tail->head);
                    p2->head->tail = p1;
                }
                if(p1->head != nullptr){
                    swap(p2->head->tail,p1->head->tail);
                    p1->tail->head = p2;
                }
                if(p1->head == nullptr && p2->tail == nullptr) {
                    swap(p1->tail->head,p2->head->tail);
                }
            }
            else{
                swap(p1->head->tail,p2->tail->head);
                swap(p1->tail->head,p2->head->tail);
            }
            *buff = p2->tail;
            p2->tail = p1->tail;
            p1->tail = *buff;
            *buff = p1->head;
            p1->head = p2->head;
            p2->head = *buff;
            delete buff;
            cout << '\n';
            outList(begin);
        }
    }
     void ihw (int k ){
        if(k <= len){
            srand(time(nullptr));
            for(int i = 1; i <= k; i++){
                deleteItemIndex((rand() % len) + 1);
            }
        }
        else cout <<"\t---Error---\n";
    }
};
int main() {
    bool check = true;
    char key;
    cout << "~~Choose how to create the list~~\n\t1) Fill with random\n\t2) Fill in manually\n";
    cin >> key;
    List newList(key);
    cin.clear();
    while(cin.get() != '\n');

    while(check){
        cout << "~~Choose type of operation~~\n";
        cout << "\t1)Search element\n\t2)Delete element\n\t3)Insert element\n\t4)Permutation of elements\n\t5)Individual homework\n\t6)Get length of list\n\t0)Exit\n";
        cin >> key;
        switch (key) {
            case '0':{
                check = false;
                break;
            }
            case '1':{
                cout << "~~How do you want to search element~~\n\t1) By index\n\t2) By value\n";
                cin >> key;
                switch (key) {
                    case '1':{
                        int *buff = new int;
                        cout << "~~Enter the index of element~~\n";
                        cin >> *buff;
                        ListItem * result = newList.searchItemIndex(*buff);
                        if(result) cout <<"---> "<< result->data <<'\n';
                        delete buff;
                        break;
                    }
                    case'2':{
                        int *buff = new int;
                        cout << "~~Enter the value of element~~\n";
                        cin >> *buff;
                        int result = newList.searchItemData(*buff);
                        if(result) cout <<"---> "<< result <<'\n';
                        delete buff;
                        break;
                    }
                }
                break;
            }
            case '2':{
                cout << "~~How do you want to delete element~~\n\t1) By index\n\t2) By value\n";
                cin >> key;
                switch (key) {
                    case '1':{
                        int *buff = new int;
                        cout << "~~Enter the index of element~~\n";
                        cin >> *buff;
                        newList.deleteItemIndex(*buff);
                        delete buff;
                        break;
                    }
                    case '2':{
                        int *buff = new int;
                        cout << "~~Enter the value of element~~\n";
                        cin >> *buff;
                        newList.deleteItemData(*buff);
                        delete buff;
                        break;
                    }
                }
                break;
            }
            case '3':{
                cout << "~~Enter the index of element which you want to insert and his value~~\n";
                int *index = new int, *data = new int;
                cin >> *index >> *data;
                newList.insertItem(*index,*data);
                delete index;
                delete data;
                break;
            }
            case '4':{
                cout << "~~Enter the indexes of elements which you want to swap~~\n";
                int *index1 = new int, *index2 = new int;
                cin >> *index1 >> *index2;
                newList.permutationItems(*index1,*index2);
                delete index1;
                delete index2;
                break;;
            }
            case '5' :{
                cout << "~~Enter the number of elements which you want to delete~~\n";
                int *amount = new int;
                cin >> *amount;
                newList.ihw(*amount);
                delete amount;
                break;
            }
            case '6':{
                cout << "\t~~Length of list = "<<newList.GetLen() <<" ~~\n";
                break;
            }
        }
    }
    system("pause");
    return 0;
}
