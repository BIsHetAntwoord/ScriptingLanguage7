template <typename T>
void ScriptTable::foreach(T callback)
{
    for(auto& it : this->values)
        callback(it.first, it.second);
}
