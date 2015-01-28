#ifndef HEXMAP_H
#define HEXMAP_H


class HexMap
{
    public:
        HexMap(int _mapHexSize);
        virtual ~HexMap();
    protected:
    private:

        int width;
        int height;
};

#endif // HEXMAP_H
