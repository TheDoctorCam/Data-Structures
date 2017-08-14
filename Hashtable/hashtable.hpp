template <typename K, typename V>
HashTable<K, V>::HashTable(size_t size):hashTable(prime_below(size)){
    currentSize = 0;
    prime_num = prime_below(size);
}

template <typename K, typename V>
HashTable<K,V>::~HashTable(){
    hashTable.clear();
}


template <typename K, typename V>
bool HashTable<K,V>::contains(const K& k){
    
    auto & list_itr= hashTable[myhash(k)];
    
    if (list_itr.empty() )    return false;
    for(auto itr = list_itr.begin(); itr != list_itr.end(); ++itr)
        if(itr->first == k)
            return true;
    return false;
}

template <typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> &kv)const{
    for(auto list_itr : hashTable){
        for(auto itr = list_itr.begin(); itr != list_itr.end(); ++itr){
            if(*itr == kv) return true;
        }
    }
    return false;
}


template<typename K, typename V>
void HashTable<K,V>::dump(){
    
    int index = 1;
    for(auto  wl : hashTable){
        for(auto itr = wl.begin(); itr != wl.end(); ++itr) {
            std::cout << "v[" << index << "]: " << itr->first << " " << itr->second << std::endl;
            index++;
        }
    }
}


template <typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V>&kv){
    if(match(kv) )   return false;   //pair kv already inside
    
    if(!(match(kv)) ){
        hashTable[myhash(kv.first)].push_back(kv);
        if(++currentSize > hashTable.size() )    rehash();
        return true;    //added kv to hash table
    }
    
    //Update value of kv if k found with different v
    if(contains(kv.first)){
        auto & list_itr = hashTable[ myhash( kv.first ) ];
        for(auto  itr = list_itr.begin(); itr != list_itr.end(); itr++){
            if((itr->first == kv.first) && (itr->second != kv.second))
                itr->second=kv.second;
        }
        return true;
    }
}

template <typename K, typename V>
bool HashTable<K, V>::insert(std::pair<K,V> &&kv){
    
    if(match(kv) )   return false;  //pair kv already inside
    
    if(!(contains(kv.first)) ){
        hashTable[myhash(kv.first)].push_back(std::move(kv));
        if(++currentSize > hashTable.size())    rehash();
        return true;
    }
    
    //Update value of kv if k found with different v
    if(contains(kv.first)){
        auto & list_itr = hashTable[ myhash( kv.first ) ];
        for(auto  itr = list_itr.begin(); itr != list_itr.end(); itr++){
            if((itr->first == kv.first) && (itr->second != kv.second))
                itr->second= std::move(kv.second);
        }
        return true;
    }
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K& k){
    
    if (!contains(k) )   return false;   //hashTable doesn't contain k
    
    auto itr_end = hashTable[myhash(k)].end();
    
    for(auto itr = hashTable[myhash(k)].begin(); itr != hashTable[myhash(k)].end(); ++itr)
        if (itr->first == k)  itr_end = itr;
    
    if(itr_end == hashTable[myhash(k)].end() )   return false;
    
    hashTable[myhash(k)].erase(itr_end);
    --currentSize;
    
    return true;
}

template <typename K, typename V>
void HashTable<K,V>::clear(){   makeEmpty(); }

template <typename K, typename V>
void HashTable<K,V>::rehash(){
    
    std::vector<std::list<std::pair<K,V> > > temp = hashTable;
    
    hashTable.resize(prime_below(2*hashTable.size()));
	   for(auto & newList: hashTable)
           newList.clear();
    
    currentSize=0;
    for(auto & newList: temp)
        for(auto & x : newList)
            insert(std::move(x));
}

template<typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename){
    
    std::ofstream files;
    files.open(filename);
    
    if(!files) return false;
    for(auto i : hashTable){
        for(auto itr = i.begin(); itr!=i.end(); ++itr)
            files << itr->first << " " << itr->second << std::endl;
    }
    return true;
}

template <typename K, typename V>
size_t HashTable<K,V>::hashSize(){
    return currentSize;
}

template <typename K, typename V>
size_t HashTable<K,V>::primeSize(){ return prime_num;   }

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K& k){
    
    std::hash<K>hashIndex;
    
    return hashIndex(k) % hashTable.size();
}

template <typename K, typename V>
void HashTable<K,V>::makeEmpty(){
    for(auto & wl: hashTable)
        wl.clear();
}

template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
    if (n > max_prime)
    {
        std::cerr << "** input too large for prime_below()\n";
        return 0;
    }
    
    if (n == max_prime)
    {
        return max_prime;
    }
    
    if (n <= 1)
    {
        std::cerr << "** input too small \n";
        return 0;
    }
    
    std::vector <unsigned long> v (n+1);
    setPrimes(v);
    while (n > 2)
    {
        if (v[n] == 1)  return n;
        --n;
    }
    
    return 2;
}

template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& p)
{
    int i = 0, j = 0;
    
    p[0] = 0;
    p[1] = 0;
    int n = p.capacity();
    
    for (i = 2; i < n; ++i) p[i] = 1;
    
    for( i = 2; i*i < n; ++i)
    {
        if (p[i] == 1)
            for(j = i + i ; j < n; j += i)
                p[j] = 0;
    }
}
