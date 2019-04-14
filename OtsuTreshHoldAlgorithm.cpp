#include "OtsuTreshHoldAlgorithm.h"
#include <vector>
#include <functional>
namespace  {
    std::vector<double> normalizeHistogram(const std::vector<int>& histogram, int image_size)
    {
        std::vector<double>res(256);
        for (size_t i = 0; i< 256; i++) {
            res[i] = histogram[i] / static_cast<double>(image_size);
        }
        return res;
    }

    double goldenSection(double a, double b, const std::function<double(double)>& function)
    {
        double x1, x2;
        double accuracy = 0.001;
        double goldenRatio =  (1 + std::sqrt(5)) / 2;
        while (std::fabs(b - a) > accuracy) {
                   x1 = b - (b - a) / goldenRatio;
                   x2 = a + (b - a) / goldenRatio;
                   if (function(x1) <= function(x2))
                       a = x1;
                   else
                       b = x2;
            }
        return (a+b)/2;
    }
}
OtsuTreshHoldAlgorithm::OtsuTreshHoldAlgorithm()
{

}

int OtsuTreshHoldAlgorithm::FindTreshHold(const IBrightImage &image)
{
    auto probabilities = normalizeHistogram(IBrightImage::GetBrightnessHistogram(image), image.GetSize());
    auto qt1 = [&](int t){
        double sum = 0;
        for(size_t i = 0; i < static_cast<size_t>(t); i++)
        {
            sum += probabilities[i];
        }
        return sum;
    };
    auto qt2 = [&](int t){
        double sum = 0;
        for(size_t i = static_cast<size_t>(t); i < 256; i++)
        {
            sum += probabilities[i];
        }
        return sum;
    };
    auto nu1 = [&](int t){
        double sum = 0;
        for(size_t i = 0; i < static_cast<size_t>(t); i++)
        {
            sum += i*probabilities[i] / qt1(t);
        }
        return sum;
    };
    auto nu2 = [&](int t){
        double sum = 0;
        for(size_t i = static_cast<size_t>(t); i < 256; i++)
        {
            sum += i*probabilities[i] / qt2(t);
        }
        return sum;
    };

    auto function = [&](double t)->double{
        int t_int = static_cast<int>(t);
        auto qt1_cache = qt1(t_int);
        auto nu_diff = nu1(t_int) - nu2(t_int);
        return qt1_cache*(1 - qt1_cache)*nu_diff*nu_diff;
    };
    return static_cast<int>(goldenSection(0, 255, function));
}
