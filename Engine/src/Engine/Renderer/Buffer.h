#pragma once

namespace Engine
{
  enum class ShaderDataType
  {
    NONE = 0,
    Float, Float2, Float3, Float4,
    Mat3, Mat4,
    Int, Int2, Int3, Int4,
    Bool
  };

  static uint32_t ShaderDataTypeSize(ShaderDataType type)
  {
    switch (type)
    {
    case ShaderDataType::Float:   return 4;
    case ShaderDataType::Float2:  return 4 * 2;
    case ShaderDataType::Float3:  return 4 * 3;
    case ShaderDataType::Float4:  return 4 * 4;
    case ShaderDataType::Mat3:    return 4 * 3 * 3;
    case ShaderDataType::Mat4:    return 4 * 4 * 4;
    case ShaderDataType::Int:     return 4;
    case ShaderDataType::Int2:    return 4 * 2;
    case ShaderDataType::Int3:    return 4 * 3;
    case ShaderDataType::Int4:    return 4 * 4;
    case ShaderDataType::Bool:    return 1;
    }
    EN_CORE_ASSERT(false, "Unknown Shader DataType!");
    return 0;
  }

  struct BufferElement
  {
    std::string _name;
    ShaderDataType _type;
    uint32_t _size;
    uint32_t _offset;
    bool _normalized;
    //BufferElement() = default;
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
      : _name(name), _type(type), _size(ShaderDataTypeSize(type)), _offset(0), _normalized(normalized) {}
    uint32_t GetComponentCount() const
    {
      switch (_type)
      {
      case ShaderDataType::Float:   return 1;
      case ShaderDataType::Float2:  return 2;
      case ShaderDataType::Float3:  return 3;
      case ShaderDataType::Float4:  return 4;
      case ShaderDataType::Mat3:    return 3 * 3;
      case ShaderDataType::Mat4:    return 4 * 4;
      case ShaderDataType::Int:     return 1;
      case ShaderDataType::Int2:    return 2;
      case ShaderDataType::Int3:    return 3;
      case ShaderDataType::Int4:    return 4;
      case ShaderDataType::Bool:    return 1;
      }
      EN_CORE_ASSERT(false, "Unknown Shader DataType!");
      return 0;
    }
  };

  class BufferLayout
  {
  public:
    BufferLayout() {}
    BufferLayout(const std::initializer_list<BufferElement>& elements)
      : m_Elements(elements)
    {
      // Calculate offset and stride
      uint32_t offset = 0;
      for (auto& element : m_Elements)
      {
        element._offset = offset;
        offset += element._size;
        m_Stride += element._size;
      }
    }
    inline uint32_t GetStride() const { return m_Stride; }
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
  private:
    uint32_t m_Stride = 0;
    std::vector<BufferElement> m_Elements;
  };

  class VertexBuffer
  {
  public:
    virtual ~VertexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual const BufferLayout& GetLayout() const = 0;
    virtual void SetLayout(const BufferLayout& layout) = 0;

    static VertexBuffer* Create(float* vertices, uint32_t size);
  };

  class IndexBuffer
  {
  public:
    virtual ~IndexBuffer() {}
    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;
    virtual uint32_t GetCount() const = 0;

    static IndexBuffer* Create(uint32_t* indices, uint32_t count);
  };
}