#ifndef IMAGE_FILE_MANAGER_MOCK_H_
#define IMAGE_FILE_MANAGER_MOCK_H_

class ImageFileManagerMock {
 public:
  virtual ~ImageFileManager() = default;

  bool RemoveImage(const std::string& image_name) override { (void)image_name; }

  bool StoreImage(const std::string& image_name,
                  const std::vector<char>& image_bytes) override {
    (void)image_name;
    (void)image_bytes;
  }
};

#endif  // IMAGE_FILE_MANAGER_MOCK_H_
