#ifndef IMAGE_FILE_MANAGER_INTERFACE_H_
#define IMAGE_FILE_MANAGER_INTERFACE_H_

class ImageFileManagerInterface {
 public:
  virtual ~ImageFileManagerInterface() = default;

  virtual bool RemoveImage(const std::string& image_name) = 0;

  /// @note this is not the absolute path of the image name
  virtual bool StoreImage(const std::string& image_name,
                          const std::vector<char>& image_bytes) = 0;
};

#endif  // IMAGE_FILE_MANAGER_INTERFACE_H_
